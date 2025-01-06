/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:20:42 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/11 19:17:24 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp_list;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		tmp_list = ft_lstnew(f(lst->content));
		if (!tmp_list)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, tmp_list);
		lst = lst->next;
	}
	return (new_list);
}
/*

#include <stdio.h>
#include "ft_lstnew.c"
#include "ft_lstadd_front.c"
#include "ft_lstclear.c"
#include "ft_lstadd_back.c"

void *add(void *content)
{
	int *new_value = malloc(sizeof(int));
	if (new_value == NULL)
		return (NULL);
	*new_value = (*(int *)content) + 1;
	return (new_value);
}



void print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d -> ", *(int *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

void del(void *content)
{
	free(content);
}

int main()
{
	int i = 0;
	t_list *liste = NULL;
	t_list *result = NULL;

	while (i < 5)
	{
		int *value = malloc(sizeof(int));
		*value = i;
		ft_lstadd_front(&liste, ft_lstnew((void *)value));
		i++;
	}

	printf("Contenu de la liste : ");
	print_list(liste);

	result = ft_lstmap(liste, add, del);
	printf("Liste apres application de la fonction : ");
	print_list(result);

	return 0;
}
*/