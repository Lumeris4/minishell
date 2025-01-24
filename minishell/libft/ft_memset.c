/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:28:30 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:28:30 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t					i;
	unsigned char			*str;

	i = 0;
	str = (unsigned char *)s;
	while (i != n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
int main()
{
	char str[6] = "essai";
	size_t n = 5;
	ft_memset((void *)str, '4',n);
	printf("%s",str);
}
*/
/*
#include <stdio.h>
int main()
{
	char str[6] = "essai";
	size_t n = 5;
	ft_memset((void *)str, '4',n);
	printf("%s",str);
}
*/
