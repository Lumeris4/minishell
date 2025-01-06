/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:16:29 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/06 15:34:36 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>

void	ft_cd(char *input);
void	ft_pwd(char **envp);
void	ft_echo(char *input, char **envp);
void	ft_yes(void);

#endif