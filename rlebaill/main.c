/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:03:24 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/07 14:01:43 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_i = 0;

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_command(char *input, char **envp)
{
	char	**split;

	split = ft_split_quote(input);
	if (ft_strncmp(input, "echo", 4) == 0 && (!input[4] || input[4] == ' '))
		ft_echo(input, envp);
	else if (ft_strncmp(input, "cd", 2) == 0 && (!input[2] || input[2] == ' '))
		ft_cd(input);
	else if (ft_strncmp(input, "./", 2) == 0)
		ft_exec(input, envp);
	else if (ft_strncmp(input, "export", 6) == 0
		&& (!input[6] || input[6] == ' '))
		ft_export(input, envp);
	else if (*input)
	{
		ft_shell(envp, input);
		wait(NULL);
	}
	ft_free_split(split);
}

void	ft_ctrl_c(int sig)
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

static int	ft_open_quote(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (!s[i])
				return (ft_printf("open quote\n"), 1);
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (!s[i])
				return (ft_printf("open quote\n"), 1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**env;

	env = copy_env(envp);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1 || ac || av[0])
	{
		input = readline("minishell> ");
		if (!input)
			return (ft_free_env(env), ft_printf("exit\n"), 0);
		if (ft_strncmp(input, "exit", 4) == 0 && (!input[4] || input[4] == ' '))
			return (ft_free_env(env), free(input), 0);
		if (*input && !ft_open_quote(input))
		{
			add_history(input);
			ft_command(input, env);
		}
		free(input);
	}
	return (0);
}
