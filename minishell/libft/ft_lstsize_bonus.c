/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:28:03 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:28:03 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*
#include "ft_lstadd_front.c"
#include "ft_lstnew.c"
#include <stdio.h>
int main ()
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
	printf("taille liste : %d",ft_lstsize(liste));
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