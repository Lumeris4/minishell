/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:21:04 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/21 15:47:49 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	setup_input_redirection(char **args, int *i)
{
	int	fd;

	if (!args[*i + 1])
	{
		perror("Redirection file missing");
		free_array(args);
		return (-1);
	}
	fd = open(args[*i + 1], O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file for input redirection");
		free_array(args);
		return (-1);
	}
	args[*i] = NULL;
	(*i)++;
	return (fd);
}


int	ft_other_redirection(char *input)
{
	int		fd;
	int		save_stdin;
	char	**args;
	int		i;

	args = ft_split_quote(input);
	if (!args || !args[0])
	{
		perror("No command provided");
		free_array(args);
		return (-1);
	}
	save_stdin = dup(STDIN_FILENO);
	if (save_stdin == -1)
	{
		perror("Failed to save stdin");
		free_array(args);
		return (-1);
	}
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<") == 0)
		{
			fd = setup_input_redirection(args, &i);
			if (dup2(fd, STDIN_FILENO) == -1)
				return (-1);
			close(fd);
		}
		else
			i++;
	}
	free_array(args);
	return(save_stdin);
}
