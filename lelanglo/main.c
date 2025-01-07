/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:08:40 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/07 15:51:35 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_shell(char **envp, char *input)
{
	pid_t	pid;
	char	**args;
	char	*cmd_path;
	int		i;

	args = ft_split(input, ' ');
	if (!args || !args[0])
	{
		free(args);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0)
		{
			free(args[i]);
			args[i] = NULL;
			break ;
		}
		i++;
	}
	if (ft_strchr(input, '>') != NULL)
	{
		ft_redirection(input);
	}
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
			exit(EXIT_FAILURE);
	}
	i = 0;
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

static void	ft_ctrl_c(int sig)
{
	(void)sig;
	if (waitpid(-1, NULL, WNOHANG) == 0)
	{
		ft_printf("\n");
		return ;
	}
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (argc && argv[0])
	{
		input = readline("Minishell ");
		if (!input)
			break ;
		if (*input && ft_strlen(input) > 0)
		{
			add_history(input);
			if (ft_strncmp(input, "exit", 4) == 0
				&& (!input[4] || input[4] == ' '))
				break ;
			if (ft_strncmp(input, "cd", 2) == 0
				&& (!input[2] || input[2] == ' '))
				ft_cd(input);
			else
			{
				ft_shell(envp, input);
				wait(NULL);
			}
		}
		free(input);
	}
	return (free(input), 0);
}
