/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:53:06 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/09 15:13:38 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>

# define KGRN "\x1B[32m"

void	ft_redirection(char *input, char **envp, int number);
int		ft_strcmp(char *s1, char *s2);
void	ft_shell(char **envp, char *input);
void	free_array(char **array);
char	**ft_split_quote(char *s);

#endif