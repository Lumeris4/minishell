/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:27:16 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/22 10:52:35 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_in_order(t_list *export, char *arg)
{
	t_list	*lst;
	t_list	*node;
	char	*dup;

	lst = export;
	dup = ft_strdup(arg);
	if (!dup)
		return ;
	node = ft_lstnew(dup);
	if (!node)
		return ;
	while (lst->next)
	{
		if (ft_strcmp(lst->next->content, arg) > 0)
		{
			node->next = lst->next;
			lst->next = node;
			return ;
		}
		lst = lst->next;
	}
	ft_lstadd_back(&export, node);
}

int	ft_in_env(char *arg, t_list *env)
{
	t_list	*lst;
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
	new = ft_strdup(arg);
	while (new[i] && new[i] != '=')
		i++;
	if (new[i])
		new[i + 1] = '\0';
	else
	{
		tmp = create_new(new);
		free(new);
		new = tmp;
	}
	lst = env;
	while (lst)
	{
		if (ft_strncmp(new, lst->content, ft_strlen(new)) == 0)
			return (free(new), 1);
		lst = lst->next;
	}
	return (free(new), 0);
}

void	ft_replace_arg(char *arg, t_mini *mini)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * 3);
	new[0] = ft_strdup("unset");
	new[1] = ft_strdup(arg);
	new[2] = NULL;
	i = 0;
	while (new[1][i] && new[1][i] != '=')
		i++;
	new[1][i] = '\0';
	ft_unset(new, mini);
	free(new[0]);
	free(new[1]);
	free(new);
}

static void	ft_remove_node(t_list **env, t_list *lst)
{
	t_list	*i;

	i = *env;
	while (i->next != lst)
		i = i->next;
	i->next = i->next->next;
	ft_lstdelone(lst, free);
}

void	ft_search_and_delete(t_list **env, char **split)
{
	t_list	*lst;
	int		i;

	i = 0;
	if (!env || !*env || !split || !split[0])
		return ;
	while (split[++i])
	{
		lst = *env;
		while (lst)
		{
			if (ft_strncmp(split[i], lst->content, ft_strlen(split[i])) == 0
				&& lst->content[ft_strlen(split[i])] == '=')
			{
				ft_remove_node(env, lst);
				break ;
			}
			lst = lst->next;
		}
	}
}
