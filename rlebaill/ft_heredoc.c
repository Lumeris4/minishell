/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:30:56 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/22 17:51:29 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_stop_word(char **args, int *index)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
		{
			*index = i;
			if (args[i + 1])
				return (ft_strdup(args[i + 1]));
			else
				ft_putstr_fd("Error: No delimiter word\n", 2);
		}
		i++;
	}
	*index = -1;
	return (NULL);
}

int	ft_heredoc(char **args)
{
	char	*stop;
	int		heredoc_index;
	int		fd;
	char	*line;

	stop = ft_get_stop_word(args, &heredoc_index);
	if (!stop || heredoc_index == -1)
		return (127);
	fd = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Unable to create heredoc file\n", 2);
		return (free(stop), 127);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, stop) == 0)
			return (free(line), free(stop), close(fd), 0);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	return (close(fd), free(stop), 0);
}
