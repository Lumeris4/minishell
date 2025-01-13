/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:08:28 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/13 14:39:39 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	execute_command(char **envp, char **args)
{
	pid_t	pid;
	char	*cmd_path;

	cmd_path = ft_strjoin("/usr/bin/", args[0]);
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
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
	free(cmd_path);
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	ft_direction(char *input, char **envp, char **args)
{
	char	*cut;

	cut = ft_strchr(input, '>');
	if (cut && cut[1] == '>')
		ft_redirection(input, envp);
	else if (ft_strchr(input, '>') != NULL)
		ft_redirection(input, envp);
	else
		execute_command(envp, args);
}

void	ft_shell(char **envp, char *input)
{
	char	**args;
	int		i;

	args = ft_split_quote(input);
	if (!args || !args[0])
	{
		free(args);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">>") == 0)
		{
			free(args[i]);
			args[i] = NULL;
			break ;
		}
		else if (ft_strcmp(args[i], ">") == 0)
		{
			free(args[i]);
			args[i] = NULL;
			break ;
		}
		i++;
	}
	ft_direction(input, envp, args);
	free_array(args);
}
