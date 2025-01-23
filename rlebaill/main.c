/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:03:24 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/22 12:52:27 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	g_mini;

int	ft_command(char **split, char ***to_free, char *input, t_mini *mini)
{
	if (!split)
		return (1);
	if (ft_strcmp(split[0], "cd") == 0)
		return (ft_cd(split, mini->env, mini));
	if (ft_strcmp(split[0], "exit") == 0)
		return (ft_exit(split, mini, to_free, input));
	if (ft_strcmp(split[0], "echo") == 0)
		return (ft_echo(split));
	if (ft_strcmp(split[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(split[0], "export") == 0)
		return (ft_export(split, mini));
	if (ft_strcmp(split[0], "unset") == 0)
		return (ft_unset(split, mini));
	if (ft_strcmp(split[0], "env") == 0)
		return (ft_env(mini->env));
	if (ft_strncmp(split[0], "./", 2) == 0)
		return (ft_exec(split, mini->envp));
	if (*split[0])
		return (ft_shell(mini->envp, split, mini));
	return (0);
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
	g_mini.last_status = 130;
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

	if (!envp || !envp[0])
		return (ft_putstr_fd(" empty environment\n", 2), 1);
	g_mini.last_status = 0;
	g_mini.env = ft_env_in_list(envp);
	g_mini.export = ft_env_sorted_in_list(&g_mini);
	if (!g_mini.export || !g_mini.env)
		return (1);
	g_mini.envp = envp;
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1 || ac || av[0])
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		else if (*input && !ft_open_quote(input))
			g_mini.last_status = ft_execute(input, &g_mini);
		else
			g_mini.last_status = 0;
		add_history(input);
		free(input);
	}
	ft_lstclear(&g_mini.export, free);
	return (ft_printf("exit\n"), ft_lstclear(&g_mini.env, free), free(input),
		rl_clear_history(), g_mini.last_status);
}
