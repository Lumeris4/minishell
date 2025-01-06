/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:37:38 by lelanglo          #+#    #+#             */
/*   Updated: 2024/11/08 14:08:16 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_unsigned_fd(unsigned long n, int fd)
{
	if (n >= 10)
		ft_putnbr_unsigned_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

static int	ft_divise(unsigned long nb)
{
	int	result;

	result = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		result++;
	}
	return (result);
}

int	ft_unsigned_decimal(unsigned int integer, int size)
{
	unsigned long	integer_long;

	integer_long = (unsigned long)integer;
	ft_putnbr_unsigned_fd(integer_long, 1);
	return (size + ft_divise(integer_long));
}

/*
#include <stdio.h>
int main()
{
	int test = ft_unsigned_decimal(2,1);
	printf("\n");
	int result = printf("%u\n",2);
	printf("%d\n", test);
	printf("%d\n",result);
	return (0);
}
*/