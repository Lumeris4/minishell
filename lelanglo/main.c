/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:08:40 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/06 13:26:17 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_pwd(char **envp)
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
		args[0] = "/usr/bin/pwd";
		args[1] = NULL;
		if (execve(args[0], args, envp) == -1)
		{
			perror("Error executing pwd");
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	pid_t	pid;

	while (argc && argv[0])
	{
		input = readline("Minishell ");
		if (!input || ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			break ;
		}
		if (ft_strncmp(input, "pwd", 3) == 0)
		{
			ft_pwd(envp);
			wait(&pid);
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		free(input);
	}
	ft_printf("Bye!\n");
	return (0);
}
