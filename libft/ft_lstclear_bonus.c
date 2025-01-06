/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:27:39 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:27:39 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*parcours;
	t_list	*parcours2;

	if (lst == NULL || del == NULL)
		return ;
	parcours = *lst;
	while (parcours)
	{
		parcours2 = parcours;
		parcours = parcours->next;
		del(parcours2->content);
		free(parcours2);
	}
	*lst = NULL;
}
/*
#include <stdio.h>
#include "ft_lstnew.c"
#include "ft_lstadd_front.c"

void del_elm(void *content)
{
	free(content);
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


int main()
{
	int i = 0;
	t_list *liste = NULL;

	while (i < 5)
	{
		int *value = malloc(sizeof(int));
		*value = i;
		ft_lstadd_front(&liste, ft_lstnew((void *)value));
		i++;
	}

	printf("Contenu de la liste : ");
	print_list(liste);

	ft_lstclear(&liste, del_elm);
	printf("Liste apres suppression : ");
	print_list(liste);

	return 0;
}
*/