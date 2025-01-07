/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:08:28 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/07 15:31:20 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**find_name_file(char *input)
{
	char	*result;
	char	**split;

	result = ft_strchr(input, '>');
	if (!result)
		return (NULL);
	result++;
	while (*result == ' ')
		result++;
	split = ft_split(result, ' ');
	return (split);
}

void	ft_redirection(char *input)
{
	int		fd;
	char	**result;
	int		i;

	result = find_name_file(input);
	if (!result || !result[0])
	{
		perror("No file for redirection");
		return ;
	}
	fd = open(result[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Failed to open file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect stdout");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}
