/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charachter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:36:55 by lelanglo          #+#    #+#             */
/*   Updated: 2024/11/08 14:06:59 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	charachter(int c, int size)
{
	ft_putchar_fd(c, 1);
	return (size + 1);
}
/*
int main ()
{
	charachter('j');
	return 0;
}
*/