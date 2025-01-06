/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_hexa_lower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:37:20 by lelanglo          #+#    #+#             */
/*   Updated: 2024/11/08 14:07:52 by lelanglo         ###   ########.fr       */
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
	ft_putchar_fd(LOWERCASE[adress % 16], 1);
	i++;
	return (i);
}

int	num_hexa_lower(unsigned int num, int size)
{
	int	result;

	result = ft_putnbr_hexa(num);
	return (size + result);
}
/*
int main()
{
	num_hexa_lower(25467, 1);
}
*/