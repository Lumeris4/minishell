/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:28:48 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:28:48 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	write(fd, str, i);
}
/*
#include <fcntl.h>
int main (void)
{
	int fd = open("test.txt", O_CREAT | O_RDWR, 0644);
	ft_putstr_fd("Mathurin le raleur", fd);
}
*/