/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:54:04 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/22 14:56:59 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_list *env)
{
	t_list	*lst;

	lst = env;
	while (lst)
	{
		ft_printf("declare -x %s\n", lst->content);
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
	char	*tmp1;
	char	**tmp2;
	char	*tmp3;
	char	*path;

	tmp1 = ft_getenv("PATH", mini);
	if (!tmp1)
		return (NULL);
	tmp2 = ft_split(tmp1, ':');
	if (!tmp2)
		return (NULL);
	tmp3 = ft_strjoin(tmp2[5], "/");
	if (!tmp3)
		return (ft_free_split(tmp2), NULL);
	path = ft_strjoin(tmp3, cmd);
	if (!path)
		return (ft_free_split(tmp2), free(tmp3), NULL);
	return (ft_free_split(tmp2), free(tmp3), path);
}
