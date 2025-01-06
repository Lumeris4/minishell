/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:37:34 by lelanglo          #+#    #+#             */
/*   Updated: 2024/11/08 14:08:13 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	string(char *str, int size)
{
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (size + 6);
	}
	ft_putstr_fd(str, 1);
	return (size + ft_strlen(str));
}
