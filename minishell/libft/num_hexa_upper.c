/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_hexa_upper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:37:24 by lelanglo          #+#    #+#             */
/*   Updated: 2024/11/08 14:08:00 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_hexa(unsigned int adress)
{
	int	i;

	i = 0;
	if (adress >= 16)
	{
		i += ft_putnbr_hexa(adress / 16);
	}
	ft_putchar_fd(UPPERCASE[adress % 16], 1);
	i++;
	return (i);
}

int	num_hexa_upper(unsigned int num, int size)
{
	int	result;

	result = ft_putnbr_hexa(num);
	return (size + result);
}
/*
#include <stdio.h>
int main()
{
	int result2 = num_hexa_upper(25467, 0);
	int result = printf("%X",25467);
	printf("%d",result);
	printf("%d",result2);
}
*/