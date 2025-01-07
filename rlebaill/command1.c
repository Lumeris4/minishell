/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:26:34 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/07 14:18:08 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *input)
{
	char	**split;
	int		i;

	split = ft_split_quote(input);
	if (!split)
		return ;
	if (chdir(split[1]) != 0)
		ft_putstr_fd("Error: incorrect folder\n", 2);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_echo(char *input, char **envp)
{
	char		**split;
	int			i;
	static char	path[9] = "/bin/echo";

	split = ft_split_quote(input);
	if (!split)
		return ;
	if (fork() == 0)
		execve(path, split, envp);
	wait(NULL);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_shell(char **envp, char *input)
{
	pid_t	pid;
	char	**args;
	char	*cmd_path;
	int		i;

	i = 0;
	args = ft_split_quote(input);
	if (!args)
		exit(EXIT_FAILURE);
	cmd_path = ft_strjoin("/usr/bin/", args[0]);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			ft_printf("command not found: %s\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}
	while (args[i])
		free(args[i++]);
	free(args);
	free(cmd_path);
}

void	ft_exec(char *input, char **envp)
{
	char	**split;

	split = ft_split_quote(input);
	if (!split[0][2])
	{
		ft_printf("permission denied: ./\n");
		return ;
	}
	if (fork() == 0)
	{
		if (execve(&split[0][2], split, envp) == -1)
		{
			ft_printf("file not found : %s\n", &split[0][2]);
			exit (0);
		}
	}
	wait(NULL);
}
