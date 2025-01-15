/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:30:56 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/15 12:55:33 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ft_get_stop_word(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
			return (ft_strdup(args[i + 1]));
		i++;
	}
	return (NULL);
}

static void	ft_add_to_list(t_list **head, char *line)
{
	t_list	*new_node;
	t_list	*current;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(line);
	new_node->next = NULL;
	if (!*head)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

static void	ft_read_heredoc(t_list **head, char *stop)
{
	char	*other_input;

	*head = NULL;
	while (1)
	{
		other_input = readline("> ");
		if (!other_input || (stop && ft_strcmp(other_input, stop) == 0))
		{
			free(other_input);
			break ;
		}
		ft_add_to_list(head, other_input);
		free(other_input);
	}
}

static void	ft_print_and_free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		ft_printf("%s\n", head->content);
		free(head->content);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	ft_heredoc(char *input)
{
	char	**args;
	char	*stop;
	t_list	*head;

	args = ft_split_quote(input);
	if (!args)
		return ;
	stop = ft_get_stop_word(args);
	if (!stop)
	{
		free_array(args);
		return ;
	}
	ft_read_heredoc(&head, stop);
	ft_print_and_free_list(head);
	free_array(args);
	free(stop);
}
