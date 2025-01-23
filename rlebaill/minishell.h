/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:16:29 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/22 18:12:23 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_mini
{
	char	**envp;
	t_list	*env;
	t_list	*export;
	int		last_status;
}	t_mini;

int		ft_other_redirection(char *input, t_mini *mini);
char	*create_new(char *new);
int		ft_redirection(char **args);
char	*ft_get_stop_word(char **args, int *index);
int		have_right(char **split);
int		have_double_left(char **split);
int		ft_heredoc(char **args);
int		ft_fill_word(char *word, char *s, t_mini *mini, int *i);
char	*ft_strdup_dollar(char *s);
void	ft_len_env_var(char *s, t_mini *mini, int *i, int *len);
int		ft_put_env_var(char *s, char *word, t_mini *mini, int *i);
int		ft_count_letters(char *s);
void	ft_is_numeric(char *str, unsigned char *exit_code);
void	ft_print_env(t_list *env);
void	ft_replace_arg(char *arg, t_mini *mini);
int		ft_in_env(char *arg, t_list *env);
void	ft_add_in_order(t_list *export, char *arg);
void	show_split(char **split);
//void	show_splited_split(char ***splited_split);
int		ft_pwd(void);
int		ft_open_pipe(char **split);
int		to_ignore(char c);
int		ft_command(char **split, char ***to_free, char *input, t_mini *mini);
int		ft_execute(char *input, t_mini *mini);
int		ft_strcmp(char *s1, char *s2);
int		ft_get_size_mat(char **env);
t_list	*ft_env_in_list(char **envp);
t_list	*ft_env_sorted_in_list(t_mini *mini);
int		ft_unset(char **split, t_mini *mini);
int		ft_export(char **split, t_mini *mini);
char	*ft_findpath(char *cmd, t_mini *mini);
int		ft_shell(char **envp, char **args, t_mini *mini);
int		ft_exit(char **split, t_mini *mini, char ***to_free, char *input);
int		ft_env(t_list *env);
void	ft_ctrl_c(int sig);
int		ft_exec(char **split, char **envp);
int		ft_have_rights(char *path);
char	*ft_getenv(char *str, t_mini *mini);
int		ft_cd(char **split, t_list *env, t_mini *mini);
int		ft_echo(char **split);
char	**ft_split_quote(char *input, t_mini *mini);
void	ft_free_split(char **split);
void	ft_free_splited_split(char ***splited_split);
int		ft_special_caractere(char *str, char **split, int j);
int		ft_dubble_red(char *s, int i);
int		ft_count_red(char *s, int i);
void	ft_search_and_delete(t_list **env, char **split);
void	ft_fill_pipe(char ***splited_split,
			int fd[2], int prev_fd, t_mini *mini);
int		ft_direction(char **split, char ***splited_split,
			char *input, t_mini *mini);

#endif