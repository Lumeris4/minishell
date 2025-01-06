/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointeur_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:37:27 by lelanglo          #+#    #+#             */
/*   Updated: 2024/11/08 14:08:05 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_hexa(unsigned long long adress)
{
	int	i;

	i = 0;
	if (adress >= 16)
	{
		i += ft_putnbr_hexa(adress / 16);
	}
	ft_putchar_fd(LOWERCASE[adress % 16], 1);
	i++;
	return (i);
}

int	ft_pointeur_hexa(void *ptr, int size)
{
	unsigned long long	adress;
	int					result;

	adress = (unsigned long long)ptr;
	if (adress == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (size + 5);
	}
	ft_putstr_fd("0x", 1);
	result = ft_putnbr_hexa(adress);
	return (size + result + 2);
}
/*
#include <stdio.h>
int main()
{
	int a = 42;
	int *ptr = &a;
	int b = 12;
	int *ptr2 = &b;
	int result = printf("%p\n", (void *)ptr);
	int result2 = ft_pointeur_hexa((void *)ptr2, 0);
	printf("\n");
	printf("%d\n",result);
	printf("%d\n",result2);
	ft_pointeur_hexa((void *)ptr, 0);
}
*/
