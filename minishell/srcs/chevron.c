/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:08:28 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/24 10:45:20 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_matdup(char **split)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * (ft_get_size_mat(split) + 1));
	while (split[i] && ft_strcmp(split[i], ">") != 0
		&& ft_strcmp(split[i], ">>") != 0
		&& ft_strcmp(split[i], "<") != 0 && ft_strcmp(split[i], "<<") != 0)
	{
		new[i] = ft_strdup(split[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
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

int	execute_command(char **split, int save_fds[2],
	char ***splited_split, t_mini *mini)
{
	int		status;
	char	**args;
	int		fd;

	args = ft_matdup(split);
	if (!args || !args[0])
	{
		if (args)
			free(args);
		dup2(save_fds[0], STDOUT_FILENO);
		dup2(save_fds[1], STDIN_FILENO);
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
	status = ft_command(args, splited_split, mini->input, mini);
	parent_process(save_fds[0], save_fds[1]);
	return (ft_free_split(args), status);
}

static int	many_chevrons(char *input)
{
	int	i;
	int	count[2];

	i = 0;
	count[0] = 0;
	count[1] = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			count[input[i] == '>']++;
			count[input[i] == '<'] = 0;
			if (count[0] > 2 || count[1] > 2)
				return (write(2, "too many chevrons\n", 18), 0);
		}
		else
		{
			count[0] = 0;
			count[1] = 0;
		}
		i++;
	}
	return (1);
}

int	ft_direction(char **split, char ***splited_split,
	char *input, t_mini *mini)
{
	int		status;
	int		save_fds[2];

	save_fds[0] = -2;
	save_fds[1] = -2;
	if (!many_chevrons(input))
		return (127);
	if (have_double_left(split))
		status = ft_heredoc(split);
	else if (have_left(split))
	{
		save_fds[1] = ft_other_redirection(input, mini);
		if (save_fds[1] == -1)
			return (127);
	}
	if (have_right(split))
		save_fds[0] = ft_redirection(split);
	if (save_fds[0] != -1 && save_fds[1] != -1)
		return (execute_command(split, save_fds, splited_split, mini));
	return (127);
}
