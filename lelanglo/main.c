/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:08:40 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/06 15:57:32 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_shell(char **envp, char *input)
{
	pid_t	pid;
	char	**args;
	char	*cmd_path;
	int		i;

	i = 0;
	args = ft_split(input, ' ');
	if (!args || !args[0])
	{
		free(args);
		exit(EXIT_FAILURE);
	}
	cmd_path = ft_strjoin("/usr/bin/", args[0]);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
			exit(EXIT_FAILURE);
	}
	while (args[i])
		free(args[i++]);
	free(args);
	free(cmd_path);
}

static void	ft_cd(char *input)
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	while (argc && argv[0])
	{
		input = readline("Minishell ");
		if (!input || (ft_strncmp(input, "exit", 4) == 0
				&& (!input[4] || input[4] == ' ')))
		{
			free(input);
			break ;
		}
		if ((ft_strncmp(input, "cd", 2) == 0
				&& (!input[2] || input[2] == ' ')))
			ft_cd(input);
		else if (input)
		{
			ft_shell(envp, input);
			wait(NULL);
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		free(input);
	}
	return (0);
}
