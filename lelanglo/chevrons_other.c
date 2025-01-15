/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:21:04 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/15 14:13:59 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	setup_input_redirection(char **args, int *i)
{
	int	fd;

	if (!args[*i + 1])
	{
		perror("Redirection file missing");
		free_array(args);
		exit(EXIT_FAILURE);
	}
	fd = open(args[*i + 1], O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file for input redirection");
		free_array(args);
		exit(EXIT_FAILURE);
	}
	args[*i] = NULL;
	(*i)++;
	return (fd);
}

static void	execute_command(char **args, char **envp, int save_stdin)
{
	char	*cmd_path;
	pid_t	pid;

	cmd_path = ft_strjoin("/usr/bin/", args[0]);
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		dup2(save_stdin, STDIN_FILENO);
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
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	free(cmd_path);
}

void	ft_other_redirection(char *input, char **envp)
{
	int		fd;
	int		save_stdin;
	char	**args;
	int		i;

	args = ft_split_quote(input);
	if (!args || !args[0])
	{
		perror("No command provided");
		free_array(args);
		return ;
	}
	save_stdin = dup(STDIN_FILENO);
	if (save_stdin == -1)
	{
		perror("Failed to save stdin");
		free_array(args);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<") == 0)
		{
			fd = setup_input_redirection(args, &i);
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("Failed to redirect stdin");
				close(fd);
				free_array(args);
				exit(EXIT_FAILURE);
			}
			close(fd);
		}
		else
			i++;
	}
	execute_command(args, envp, save_stdin);
	free_array(args);
}
