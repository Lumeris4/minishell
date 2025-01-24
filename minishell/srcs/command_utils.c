/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:54:04 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/24 09:17:50 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_list *env)
{
	t_list	*lst;
	int		i;
	int		status;

	lst = env;
	while (lst)
	{
		status = 1;
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while (lst->content[i])
		{
			ft_putchar_fd(lst->content[i], 1);
			if (lst->content[i] == '=' && status)
			{
				status = 0;
				ft_putchar_fd('"', 1);
			}
			i++;
		}
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		lst = lst->next;
	}
}

void	ft_is_numeric(char *str, unsigned char *exit_code)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i])
			&& str[i] != '-' && str[i] != '+')
		{
			ft_putstr_fd(" numeric argument required\n", 2);
			*exit_code = 2;
			return ;
		}
	}
}

char	*create_new(char *new)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(new) + 2));
	ft_strlcpy(tmp, new, ft_strlen(new) + 1);
	tmp[ft_strlen(new)] = '=';
	tmp[ft_strlen(new) + 1] = '\0';
	return (tmp);
}

char	*ft_getenv(char *str, t_mini *mini)
{
	t_list	*lst;

	lst = mini->env;
	while (lst)
	{
		if (ft_strncmp(str, lst->content, ft_strlen(str)) == 0
			&& lst->content[ft_strlen(str)] == '=')
			return (ft_strchr(lst->content, '=') + 1);
		lst = lst->next;
	}
	return (NULL);
}

char	*ft_findpath(char *cmd, t_mini *mini)
{
	char	*path;

	if (cmd[0] && cmd[0] == '/')
	{
		path = ft_strdup(cmd);
		if (!path)
			return (NULL);
		return (path);
	}
	if (!ft_getenv("PATH", mini))
		return (NULL);
	path = ft_strjoin("/usr/bin/", cmd);
	return (path);
}
