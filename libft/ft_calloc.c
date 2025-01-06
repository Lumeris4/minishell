/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:25:48 by lelanglo          #+#    #+#             */
/*   Updated: 2024/10/09 21:25:48 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset((unsigned char *)ptr, 0, nmemb * size);
	return (ptr);
}
/*
#include <stdio.h>

int main() {
    int *arr;
    int n = 5;
    int i = 0;

    arr = (int*) ft_calloc(n, sizeof(int));
    if (arr == 0) 
        return 0;

    while (i < n)
    {
        printf("%d ", arr[i]);
        i++;
    }
    free(arr);
    return 0;
}
*/
