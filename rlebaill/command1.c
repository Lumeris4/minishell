/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:26:34 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/06 15:47:02 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char *input)
{
	char	**split;
	int		i;

	split = ft_split(input, ' ');
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

	split = ft_split(input, ' ');
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

void	ft_pwd(char **envp)
{
	pid_t	pid;
	char	*args[2];

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		args[0] = "pwd";
		args[1] = NULL;
		if (execve("/usr/bin/pwd", args, envp) == -1)
		{
			perror("Error executing pwd");
			exit(EXIT_FAILURE);
		}
	}
	wait(NULL);
}

void	ft_yes(void)
{
	while (1)
	{
		ft_putchar_fd('y', 1);
		ft_putchar_fd('\n', 1);
	}
}
