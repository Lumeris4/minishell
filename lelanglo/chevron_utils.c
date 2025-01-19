/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:24:29 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/19 18:53:43 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	setup_redirection(char **args, int *i, int number)
{
	int	fd;

	if (!args[*i + 1])
	{
		ft_putstr_fd("Redirection file missing\n", 2);
		free_array(args);
		return (-1);
	}
	if (number == 1)
		fd = open(args[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(args[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Failed to open file\n", 2);
		free_array(args);
		return (-1);
	}
	args[*i] = NULL;
	(*i)++;
	return (fd);
}

static int	execute_command(char **args, char **envp, int save_stdout, int index)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = ft_strjoin("/usr/bin/", args[index]);
	if (!cmd_path)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			ft_putstr_fd("Execution failed\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &status, 0);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	free(cmd_path);
	return (0);
}

static int	handle_redirection(char **args, int *i)
{
	int	fd;

	if (ft_strcmp(args[*i], ">") == 0)
		fd = setup_redirection(args, i, 1);
	else
		fd = setup_redirection(args, i, 2);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	ft_redirection(char *input, char **envp)
{
	int		save_stdout;
	char	**args;
	int		i;
	int		redirection_found;

	args = ft_split_quote(input);
	if (!args || !args[0])
	{
		ft_putstr_fd("No command provided\n", 2);
		free_array(args);
		return ;
	}
	save_stdout = dup(STDOUT_FILENO);
	i = 0;
	redirection_found = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
		{
			redirection_found = 1;
			if (handle_redirection(args, &i) == -1)
			{
				free_array(args);
				return ;
			}
		}
		else
			i++;
	}
	if (redirection_found && !args[0])
	{
		dup2(save_stdout, STDOUT_FILENO);
		close(save_stdout);
	}
	else if (args[0])
		execute_command(args, envp, save_stdout, 0);
	else if (args[2])
		execute_command(args, envp, save_stdout, 2);
	free_array(args);
}

