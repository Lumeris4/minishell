/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:27:51 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:27:51 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
#include "ft_lstadd_front.c"
#include "ft_lstnew.c"
#include <stdio.h>
int main ()
{
	int i = 0;
	t_list *liste = NULL;
	while (i < 3)
	{
		int *value = malloc(sizeof(int));
		*value = i;
		ft_lstadd_front(&liste, ft_lstnew((void *)value));
		i++;
	}
	t_list *last = ft_lstlast(liste);
	printf("dernier liste : %d", *(int *)last->content);
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