/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:21:04 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/23 14:55:24 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirection_error(char **args, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_free_split(args);
	return (-1);
}

static int	setup_input_redirection(char **args, int *i)
{
	int	fd;

	if (!args[*i + 1])
		return (handle_redirection_error(args, " redirection file missing\n"));
	fd = open(args[*i + 1], O_RDONLY);
	if (fd == -1)
		return (handle_redirection_error(args,
				" failed to open file for input redirection\n"));
	(*i) += 2;
	return (fd);
}

static int	apply_redirections(char **args)
{
	int	i;
	int	fd;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<") == 0)
		{
			fd = setup_input_redirection(args, &i);
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				close(fd);
				return (handle_redirection_error(args, " dup2 failed\n"));
			}
			close(fd);
		}
		else
			i++;
	}
	return (0);
}

int	ft_other_redirection(char *input, t_mini *mini)
{
	int		save_stdin;
	char	**args;

	args = ft_split_quote(input, mini);
	if (!args || !args[0])
		return (handle_redirection_error(args, " no command provided\n"));
	save_stdin = dup(STDIN_FILENO);
	if (save_stdin == -1)
		return (handle_redirection_error(args, " dup fail\n"));
	if (apply_redirections(args) == -1)
	{
		dup2(save_stdin, STDIN_FILENO);
		close(save_stdin);
		return (-1);
	}
	ft_free_split(args);
	return (save_stdin);
}
