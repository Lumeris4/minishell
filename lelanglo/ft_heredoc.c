/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:30:56 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/22 13:30:27 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ft_get_stop_word(char **args, int *index)
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

void ft_heredoc(char *input)
{
    char    **args;
    char    *stop;
    int     heredoc_index;
    int     fd;
    char    *line;

    args = ft_split_quote(input);
    if (!args)
        return ;
    stop = ft_get_stop_word(args, &heredoc_index);
    if (!stop || heredoc_index == -1)
    {
        free_array(args);
        return ;
    }
    fd = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("Error: Unable to create heredoc file\n", 2);
        free_array(args);
        free(stop);
        return ;
    }
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, stop) == 0)
        {
            free(line);
            break ;
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
    }
    close(fd);
    free(stop);
    free_array(args);
}



