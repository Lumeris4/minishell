/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:27:58 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:27:58 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

/*
#include <stdio.h>
#include "ft_strdup.c"
#include "ft_strlen.c"
int main ()
{
	int i = 1;
	char *str = ft_strdup("test");

	t_list *liste = ft_lstnew((void *)&i);
	t_list *listes = ft_lstnew((void *)str);

	printf("%d\n", *(int *)liste->content);
	printf("%s\n",(char *)listes->content);
	return 0;
}
*/