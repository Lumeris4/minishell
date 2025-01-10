/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:24:29 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/10 09:33:37 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	give_i(char **args, int number)
{
	int	i;

	i = 0;
	if (number == 1)
	{
		while (args[i] && ft_strcmp(args[i], ">") != 0)
			i++;
	}
	else if (number == 2)
	{
		while (args[i] && ft_strcmp(args[i], ">>") != 0)
			i++;
	}
	return (i);
}

static int	setup_redirection(char **args, int number)
{
	int	fd;
	int	i;

	i = give_i(args, number);
	if (!args[i] || !args[i + 1])
	{
		perror("Redirection file missing");
		free_array(args);
		exit(EXIT_FAILURE);
	}
	if (number == 1)
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Failed to open file");
		free_array(args);
		exit(EXIT_FAILURE);
	}
	args[i] = NULL;
	return (fd);
}

static void	execute_command_with_redirection(char **args, char **envp,
		int save_stdout)
{
	char	*cmd_path;
	pid_t	pid;

	cmd_path = ft_strjoin("/usr/bin/", args[0]);
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		dup2(save_stdout, STDOUT_FILENO);
		free_array(args);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
	}
	wait(NULL);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	free(cmd_path);
}

void	ft_redirection(char *input, char **envp, int number)
{
	int		fd;
	int		save_stdout;
	char	**args;

	args = ft_split_quote(input);
	if (!args || !args[0])
	{
		perror("No command provided");
		free_array(args);
		return ;
	}
	fd = setup_redirection(args, number);
	save_stdout = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect stdout");
		close(fd);
		free_array(args);
		exit(EXIT_FAILURE);
	}
	close(fd);
	execute_command_with_redirection(args, envp, save_stdout);
	free_array(args);
}
