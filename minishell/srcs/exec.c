/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:22:04 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/24 10:40:18 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_commands(char **split)
{
	int	i;

	i = 0;
	if (ft_strcmp(split[0], "|") == 0)
		return (1);
	while (split[i] && !(ft_strcmp(split[i], "|") == 0))
		i++;
	return (i);
}

static char	**ft_extracte_command(char **split, int n)
{
	char	**command;
	int		i;
	int		j;
	int		len;

	j = -1;
	i = -1;
	len = n;
	while (++i < n)
	{
		if (!split[i][0])
			len--;
	}
	if (len == 0)
		return (NULL);
	i = 0;
	command = malloc(sizeof(char *) * (len + 1));
	while (i < n)
	{
		if (split[i][0] && !(split[i][0] == ' ' && !split[i][1]))
			command[++j] = ft_strdup(split[i]);
		i++;
	}
	command[++j] = NULL;
	return (command);
}

static char	***ft_split_split(char **split, int count, int i, int j)
{
	char	***splited_split;
	char	**tmp;

	while (split[++i])
		if (ft_strcmp(split[i], "|") == 0)
			count += 2;
	splited_split = malloc(sizeof(char **) * (count + 2));
	if (!splited_split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		count = ft_count_commands(&split[i]);
		tmp = ft_extracte_command(&split[i], count);
		if (tmp)
			splited_split[j++] = tmp;
		i += count;
	}
	return (splited_split[j] = NULL, splited_split[j + 1] = NULL,
		splited_split);
}

static int	ft_pipe(char ***splited_split, t_mini *mini)
{
	int		fd[2];
	int		i;
	int		prev_fd;
	pid_t	pid;

	prev_fd = 0;
	i = 0;
	while (splited_split[i])
	{
		if (splited_split[i + 1] && pipe(fd) == -1)
			return (127);
		pid = fork();
		if (pid == -1)
			return (127);
		if (pid == 0)
			ft_fill_pipe(&splited_split[i], fd, prev_fd, mini);
		if (prev_fd != 0)
			close(prev_fd);
		if (splited_split[i + 1])
			prev_fd = fd[0];
		close(fd[1]);
		i += 2;
	}
	waitpid(pid, &i, 0);
	return ((i >> 8) & 0xFF);
}

int	ft_execute(char *input, t_mini *mini, int *signal)
{
	char	***splited_split;
	char	**split;
	int		status;

	if (*signal == 130)
	{
		mini->last_status = 130;
		*signal = 0;
	}
	split = ft_split_quote(input, mini);
	if (ft_open_pipe(split))
		return (ft_free_split(split), 1);
	splited_split = ft_split_split(split, 1, -1, 0);
	if (!splited_split)
		return (ft_free_split(split), 1);
	ft_free_split(split);
	if (splited_split[0] && splited_split[1])
		status = ft_pipe(splited_split, mini);
	else if (splited_split[0])
		status = ft_direction(splited_split[0], splited_split, input, mini);
	else
		status = 0;
	while (wait(NULL) > 0)
		;
	return (ft_free_splited_split(splited_split), status);
}
