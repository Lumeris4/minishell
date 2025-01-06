/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:37:02 by lelanglo          #+#    #+#             */
/*   Updated: 2024/11/08 14:07:06 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_divise(long nb, int sign)
{
	int	result;

	result = 1;
	if (sign < 0)
	{
		result++;
		nb *= -1;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		result++;
	}
	return (result);
}

int	ft_decimal(int integer, int size)
{
	int		sign;
	long	nb_long;

	nb_long = (long)integer;
	sign = 1;
	if (nb_long < 0)
		sign *= -1;
	ft_putnbr_fd(integer, 1);
	return (size + ft_divise(nb_long, sign));
}
/*
#include <stdio.h>
int main()
{
	int test = ft_unsigned_decimal(-12,1);
	int result = printf("%d",-12);
	printf("%d\n", test);
	printf("%d\n",result);
	return (0);
}
*/