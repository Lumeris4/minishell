/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:37:09 by lelanglo          #+#    #+#             */
/*   Updated: 2024/11/08 14:07:16 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conversion(const char c, va_list args, int size)
{
	int		new_size;

	new_size = 0;
	if (c == 'c')
		new_size = charachter(va_arg(args, int), size);
	else if (c == 's')
		new_size = string(va_arg(args, char *), size);
	else if (c == 'p')
		new_size = ft_pointeur_hexa(va_arg(args, void *), size);
	else if (c == 'd')
		new_size = ft_decimal(va_arg(args, int), size);
	else if (c == 'i')
		new_size = ft_integer(va_arg(args, int), size);
	else if (c == 'u')
		new_size = ft_unsigned_decimal(va_arg(args, unsigned int), size);
	else if (c == 'x')
		new_size = num_hexa_lower(va_arg(args, unsigned int), size);
	else if (c == 'X')
		new_size = num_hexa_upper(va_arg(args, unsigned int), size);
	else if (c == '%')
		new_size = pourcent(size);
	return (new_size);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	size_t	i;
	int		size;

	size = 0;
	va_start(args, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			size = ft_conversion(s[i + 1], args, size);
			i++;
		}
		else
		{
			write(1, &s[i], 1);
			size++;
		}
		i++;
	}
	va_end(args);
	return (size);
}
