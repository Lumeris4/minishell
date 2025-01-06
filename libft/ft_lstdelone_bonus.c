/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:27:46 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:27:46 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
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

	printf("Contenu avant suppression :");
	print_list(liste);
	ft_lstdelone(liste, del_elm);
	liste = NULL;
	printf("Contenu apres suppression :");
	print_list(liste);
	while (liste)
	{
		t_list *temp = liste;
		liste = liste->next;
		free(temp->content);
		free(temp);
	}

	return 0;
}
*/
