/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:30:56 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/14 16:27:08 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_heredoc(char *input)
{
	char	**args;
	char	*other_input;
	char	*stop;
	int		i;

	args = ft_split_quote(input);
	i = 0;
	while(args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
			stop = ft_strdup(args[i + 1]);
		i++;
	}
	while (1)
	{
		other_input = readline("heredoc> ");
		if (ft_strcmp(other_input, stop) == 0)
			break ;
		free(other_input);
	}
	free(other_input);
	free_array(args);
	free(stop);
}
