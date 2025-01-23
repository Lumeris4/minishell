/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 09:07:09 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/22 10:40:31 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_have_equal(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '=')
		return (2);
	while (str[i] && ft_isalpha(str[i]))
		i++;
	if (str[i] == '=')
		return (1);
	if (str[i] && !ft_isalpha(str[i]))
		return (2);
	return (0);
}

static void	ft_add_to_export(char *arg, t_mini *mini)
{
	int		i;
	char	*new_arg;

	if (!ft_have_equal(arg))
	{
		new_arg = malloc(sizeof(char) * (ft_strlen(arg) + 4));
		i = -1;
		while (arg[++i])
			new_arg[i] = arg[i];
		new_arg[i] = '=';
		new_arg[i + 1] = '\'';
		new_arg[i + 2] = '\'';
		new_arg[i + 3] = '\0';
	}
	else
		new_arg = ft_strdup(arg);
	ft_add_in_order(mini->export, new_arg);
	free(new_arg);
}

int	ft_unset(char **split, t_mini *mini)
{
	if (ft_get_size_mat(split) == 1)
		return (0);
	ft_search_and_delete(&mini->env, split);
	ft_search_and_delete(&mini->export, split);
	return (0);
}

int	ft_export(char **split, t_mini *mini)
{
	t_list	*lst;
	int		i;

	lst = mini->export;
	if (ft_get_size_mat(split) == 1)
		ft_print_env(mini->export);
	else
	{
		i = 0;
		while (split[++i])
		{
			if (ft_in_env(split[i], mini->export))
				ft_replace_arg(split[i], mini);
			if (ft_have_equal(split[i]) == 1)
			{
				ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(split[i])));
				ft_add_in_order(mini->export, split[i]);
			}
			else if (ft_have_equal(split[i]) == 0)
				ft_add_to_export(split[i], mini);
			else
				return (ft_putstr_fd(" not a valid identifier\n", 2), 1);
		}
	}
	return (0);
}

int	ft_exit(char **split, t_mini *mini, char ***to_free, char *input)
{
	unsigned char	exit_code;

	(void)split;
	exit_code = 0;
	if (to_free[0][1])
		ft_is_numeric(to_free[0][1], &exit_code);
	if (to_free[0][1] && to_free[0][2])
		return (ft_putstr_fd(" too many arguments\n", 2), 1);
	else if (to_free[0][1])
	{
		if (!exit_code)
			exit_code = ft_atoi(to_free[0][1]);
		ft_printf("exit\n");
	}
	else
		ft_printf("exit\n");
	ft_lstclear(&mini->env, free);
	ft_lstclear(&mini->export, free);
	ft_free_splited_split(to_free);
	free(input);
	rl_clear_history();
	exit(exit_code);
	return (exit_code);
}
