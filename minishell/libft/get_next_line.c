/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:41:36 by lelanglo          #+#    #+#             */
/*   Updated: 2024/12/09 10:55:56 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	newline(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_new_buffer(char **buffer, int index_line)
{
	char	*result;

	if ((*buffer)[index_line + 1] == '\0')
	{
		free(*buffer);
		*buffer = NULL;
	}
	else
	{
		result = ft_substr(*buffer, index_line + 1,
				ft_strlen(*buffer) - index_line - 1);
		free(*buffer);
		*buffer = result;
	}
}

static int	reading(int fd, char **buffer)
{
	char	*second_buffer;
	int		bytes_read;
	char	*buffer_temp;

	second_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!second_buffer)
		return (0);
	bytes_read = read(fd, second_buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(second_buffer);
		return (-1);
	}
	if (bytes_read == 0)
	{
		free(second_buffer);
		return (0);
	}
	second_buffer[bytes_read] = '\0';
	buffer_temp = ft_strjoin(*buffer, (const char *)second_buffer);
	free(*buffer);
	free(second_buffer);
	*buffer = buffer_temp;
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char		*buffer = NULL;
	int				index_line;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	index_line = newline(buffer);
	while (index_line == -1 && reading(fd, &buffer) > 0)
		index_line = newline(buffer);
	if (index_line != -1)
	{
		line = ft_substr(buffer, 0, index_line + 1);
		ft_new_buffer(&buffer, index_line);
		return (line);
	}
	if (buffer != NULL && reading(fd, &buffer) == 0)
	{
		line = ft_substr(buffer, 0, ft_strlen(buffer));
		free(buffer);
		buffer = NULL;
		return (line);
	}
	free(buffer);
	return (NULL);
}

// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	int fd = open("text2.text", O_RDONLY);
// 	if (fd == -1) {
// 		perror("Erreur lors de l'ouverture du fichier");
// 		exit(EXIT_FAILURE);
// 	}
// 	char *result;
// 	int i = 0;
// 	while (i < 3)
// 	{
// 		result = get_next_line(fd);
// 		printf("%s",result);
// 		i++;
// 	}
// 	free(result);
// 	close(fd);
// }
