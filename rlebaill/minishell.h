/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:16:29 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/07 14:00:28 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>

char	**copy_env(char **envp);
void	ft_free_env(char **env);
void	ft_export(char *input, char **envp);
void	ft_shell(char **envp, char *input);
void	ft_ctrl_c(int sig);
void	ft_exec(char *input, char **envp);
void	ft_cd(char *input);
void	ft_echo(char *input, char **envp);
char	**ft_split_quote(char *input);
void	ft_free_split(char **split);

#endif