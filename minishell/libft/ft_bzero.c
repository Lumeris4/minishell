/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:25:41 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:25:41 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i != n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
int main()
{
	int n = 3;
	char str[n];

	ft_bzero((void *)str ,n);
	printf("%s",str);
	return 0;
}
*/