/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:08:28 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/22 14:42:30 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char **extract_command(char *input)
{
	char	**args;
	int		i;

	args = ft_split_quote(input);
	if (!args)
		return (NULL);
	i = 0;
	while (args[i] && ft_strcmp(args[i], ">") != 0 && ft_strcmp(args[i], ">>") != 0
		&& ft_strcmp(args[i], "<") != 0 && ft_strcmp(args[i], "<<") != 0)
		i++;
	args[i] = NULL;
	return (args);
}

static void	child_process(char *cmd_path, char **args, char **envp)
{
	if (execve(cmd_path, args, envp) == -1)
	{
		ft_putstr_fd("Execution failed\n", 2);
		exit(EXIT_FAILURE);
	}
}

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

void execute_command(char **envp, char *input, int save_fd, int save_stdin)
{
    pid_t   pid;
    char    *cmd_path;
    char    **args;

    args = extract_command(input);
    if (!args || !args[0])
    {
        dup2(save_fd, STDOUT_FILENO);
        close(save_fd);
        dup2(save_stdin, STDIN_FILENO);
        close(save_stdin);
        return ;
    }
    cmd_path = ft_strjoin("/usr/bin/", args[0]);
    pid = fork();
    if (pid == -1)
        ft_putstr_fd("Fork failed\n", 2);
    else if (pid == 0)
        child_process(cmd_path, args, envp);
    else
        parent_process(save_fd, save_stdin);
    free(cmd_path);
    free_array(args);
}

void	ft_direction(char *input, char **envp)
{
	int		save_fd;
	int		save_stdin;
	char	*char_pos;

	save_fd = -2;
	save_stdin = -2;

	if ((char_pos = ft_strchr(input, '<')))
	{
		if (*(char_pos + 1) == '<')
			ft_heredoc(input);
		else if (*(char_pos + 1) != '\0')
			save_stdin = ft_other_redirection(input);
	}
	if ((char_pos = ft_strchr(input, '>')))
		save_fd = ft_redirection(input);
	if (save_fd != -1 || save_stdin != -1)
		execute_command(envp, input, save_fd, save_stdin);
}

void	ft_shell(char **envp, char *input)
{
	ft_direction(input, envp);
}
