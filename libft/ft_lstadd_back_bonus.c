/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:26:57 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:26:57 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*parcours;

	if (lst != NULL && *lst != NULL)
	{
		parcours = *lst;
		while (parcours->next != NULL)
			parcours = parcours->next;
		parcours->next = new;
	}
	else if (lst != NULL)
		*lst = new;
}
/*
#include <stdio.h>
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

	int *value = malloc(sizeof(int));
	*value = i;
	ft_lstadd_back(&liste, ft_lstnew((void *)value));
	printf("Liste apres application de la fonction : ");
	print_list(liste);

	return 0;
}
*/