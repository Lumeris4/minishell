/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:26:48 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:26:48 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_divise(long nb, int sign)
{
	int	result;

	result = 1;
	if (sign < 0)
		result++;
	while (nb >= 10)
	{
		nb = nb / 10;
		result++;
	}
	return (result);
}

static void	result_itoa(char *result, long nn, unsigned int i, int sign)
{
	result[i] = '\0';
	result[--i] = (nn % 10) + '0';
	nn /= 10;
	while (nn > 0)
	{
		result[--i] = nn % 10 + '0';
		nn /= 10;
	}
	if (sign == -1)
		result[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*result;
	long			nn;
	unsigned int	i;
	int				sign;

	sign = 1;
	if (n < 0)
	{
		nn = (long)n * -1;
		sign = -1;
	}
	else
		nn = n;
	result = malloc(sizeof(char) * (ft_divise(nn, sign) + 1));
	if (result == NULL)
		return (NULL);
	i = ft_divise(nn, sign);
	result_itoa(result, nn, i, sign);
	return (result);
}
/*
#include <stdio.h>
int main()
{
	printf("%s\n",ft_itoa(-12456));
	return 0;
}
*/