/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:30:56 by lelanglo          #+#    #+#             */
/*   Updated: 2025/01/17 15:05:22 by lelanglo         ###   ########.fr       */
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

static char	**ft_extract_command(char **args, int heredoc_index)
{
	char	**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * (heredoc_index + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < heredoc_index)
	{
		cmd[i] = ft_strdup(args[i]);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
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

static char	*ft_find_command_path(char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*test_path;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		test_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(test_path, cmd);
		free(test_path);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
	}
	free_array(paths);
	return (NULL);
}

static void	ft_execute_with_heredoc(char **cmd, t_list *head)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*cmd_path;

	cmd_path = ft_find_command_path(cmd[0]);
	if (!cmd_path)
		return ;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execve(cmd_path, cmd, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[0]);
		while (head)
		{
			ft_putendl_fd(head->content, pipe_fd[1]);
			head = head->next;
		}
		close(pipe_fd[1]);
		free(cmd_path);
		waitpid(pid, NULL, 0);
	}
}

static void	ft_free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
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
	int		heredoc_index;
	char	**cmd;

	args = ft_split_quote(input);
	if (!args)
		return ;
	stop = ft_get_stop_word(args, &heredoc_index);
	if (!stop || heredoc_index == -1)
	{
		free_array(args);
		return ;
	}
	cmd = ft_extract_command(args, heredoc_index);
	ft_read_heredoc(&head, stop);
	ft_execute_with_heredoc(cmd, head);
	ft_free_list(head);
	free_array(args);
	free_array(cmd);
	free(stop);
}
