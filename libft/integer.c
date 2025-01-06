/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:37:16 by lelanglo          #+#    #+#             */
/*   Updated: 2024/11/08 14:07:30 by lelanglo         ###   ########.fr       */
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

int	ft_integer(int integer, int size)
{
	int		sign;
	long	i_l;

	i_l = (long)integer;
	sign = 1;
	if (integer < 0)
		sign *= -1;
	ft_putnbr_fd(i_l, 1);
	return (size + ft_divise(i_l, sign));
}
/*
#include <stdio.h>
int main()
{
	int test = ft_integer(-12,1);
	int result = printf("%i",-12);
	printf("%d\n", test);
	printf("%d\n",result);
	return (0);
}
*/