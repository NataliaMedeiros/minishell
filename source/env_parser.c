/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 13:29:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/16 15:25:36 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_find_path(char **envp, char *str) //find path -> Duda's function
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	**parsing_env_path(char **envp) //Part of Duda's function
{
	char	**path;

	path = ft_split(ft_find_path(envp, "PATH="), ':');
	if (path == NULL)
		return (error_msg("Unexpected error\n"), NULL);
	return (path);
}

static t_env	*new_env_info(char	*env)
{
	t_env	*env_list;
	char	*temp;
	int		j;

	env_list = malloc(sizeof(t_env));
	if (env_list == NULL)
		return (NULL);
	j = 0;
	while (env[j] != '=')
		j++;
	env_list->key_word = ft_calloc(sizeof(char), j + 2);
	if (env_list->key_word == NULL)
		return (NULL);
	ft_strlcpy(env_list->key_word, env, (j + 2));
	temp = ft_strtrim_adapted(env, env_list->key_word);
	env_list->info = ft_strdup(temp);
	free(temp);
	env_list->next = NULL;
	return (env_list);
}

static void	env_add_back(t_env **head, void *content)
{
	t_env	*current_node;
	t_env	*new_node;

	current_node = *head;
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}
	new_node = new_env_info(content);
	current_node->next = new_node;
}

t_env	*parsing_env(char **env)
{
	t_env	*env_list;
	int		i;

	env_list = new_env_info(env[0]);
	i = 1;
	while (env[i] != NULL)
	{
		env_add_back(&env_list, env[i]);
		i++;
	}
	return (env_list);
}
