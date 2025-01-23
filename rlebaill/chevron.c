/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:08:28 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/22 18:22:32 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**extract_command(char *input, t_mini *mini)
{
	char	**args;
	int		i;

	args = ft_split_quote(input, mini);
	if (!args)
		return (NULL);
	i = 0;
	while (args[i] && ft_strcmp(args[i], ">") != 0
		&& ft_strcmp(args[i], ">>") != 0
		&& ft_strcmp(args[i], "<") != 0 && ft_strcmp(args[i], "<<") != 0)
		i++;
	args[i] = NULL;
	return (args);
}

// static void	child_process(char *cmd_path, char **args, char **envp)
// {
// 	if (execve(cmd_path, args, envp) == -1)
// 	{
// 		ft_putstr_fd("Execution failed\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// }

static void	parent_process(int save_fd, int save_stdin)
{
	wait(NULL);
	if (save_fd >= 0)
	{
		dup2(save_fd, STDOUT_FILENO);
		close(save_fd);
	}
	if (save_stdin >= 0)
	{
		dup2(save_stdin, STDIN_FILENO);
		close(save_stdin);
	}
}

int	execute_command(char *input, int save_fds[2],
	char ***splited_split, t_mini *mini)
{
	int		status;
	char	**args;
	int		fd;

	args = extract_command(input, mini);
	if (!args || !args[0])
	{
		dup2(save_fds[0], STDOUT_FILENO);
		close(save_fds[0]);
		dup2(save_fds[1], STDIN_FILENO);
		close(save_fds[1]);
		return (127);
	}
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd != -1)
	{
		save_fds[1] = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(".heredoc_tmp");
	}
	status = ft_command(args, splited_split, input, mini);
	parent_process(save_fds[0], save_fds[1]);
	ft_free_split(args);
	return (status);
}

int	ft_direction(char **split, char ***splited_split,
	char *input, t_mini *mini)
{
	int		status;
	int		save_fds[2];
	char	*char_pos;

	save_fds[0] = -2;
	save_fds[1] = -2;
	char_pos = ft_strchr(input, '<');
	if (char_pos)
	{
		if (*(char_pos + 1) == '<')
			status = ft_heredoc(split);
		else if (*(char_pos + 1) != '\0')
			save_fds[1] = ft_other_redirection(input, mini);
	}
	if ((char_pos = ft_strchr(input, '>')))
		save_fds[0] = ft_redirection(split);
	if (save_fds[0] != -1 || save_fds[1] != -1)
		return (execute_command(input, save_fds, splited_split, mini));
	return (127);
}
