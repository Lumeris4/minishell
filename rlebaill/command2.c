/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:33:33 by rlebaill          #+#    #+#             */
/*   Updated: 2025/01/07 13:39:41 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	int		size;
	char	**env_copy;

	size = 0;
	while (envp[size])
		size++;
	env_copy = (char **)malloc((size + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_copy[size] = NULL;
	return (env_copy);
}

void	ft_sort(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], 1024) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	ft_export(char *input, char **envp)
{
	int		i;
	char	**envs;

	(void)input;
	envs = copy_env(envp);
	ft_sort(envs);
	i = 0;
	while (envs[i])
	{
		ft_putstr_fd(envs[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	ft_free_split(envs);
}
