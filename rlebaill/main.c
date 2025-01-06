/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:03:24 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/06 15:35:21 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_command(char *input, char **envp)
{
	if (ft_strncmp(input, "echo", 4) == 0 && (!input[4] || input[4] == ' '))
		ft_echo(input, envp);
	else if (ft_strncmp(input, "yes", 3) == 0 && (!input[3] || input[3] == ' '))
		ft_yes();
	else if (ft_strncmp(input, "pwd", 3) == 0 && (!input[3] || input[3] == ' '))
		ft_pwd(envp);
	else if (ft_strncmp(input, "cd", 2) == 0 && (!input[2] || input[2] == ' '))
		ft_cd(input);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	while (ac && av[0])
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (ft_strncmp(input, "exit", 4) == 0 && (!input[4] || input[4] == ' '))
			break ;
		ft_command(input, envp);
		if (*input)
			add_history(input);
		free(input);
	}
	return (free(input), 0);
}
