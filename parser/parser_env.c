/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 13:29:47 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/29 13:50:39 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*new_env(char	*env)
{
	t_env	*env_list;
	char	*temp;
	int		i;

	env_list = malloc(sizeof(t_env));
	if (env_list == NULL)
		return (error_msg("Erro to create env node\n"), NULL);
	i = 0;
	while (env[i] != '=')
		i++;
	env_list->key_word = ft_calloc(sizeof(char), i + 2);
	if (env_list->key_word == NULL)
		return (free(env_list), NULL);
	ft_strlcpy(env_list->key_word, env, (i + 2));
	temp = ft_strtrim_beginning(env, env_list->key_word);
	env_list->info = ft_strdup(temp);
	free(temp);
	env_list->next = NULL;
	return (env_list);
}

static void	add_env_back(t_env **head, void *content)
{
	t_env	*current_node;
	t_env	*new_node;

	current_node = *head;
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}
	new_node = new_env(content);
	current_node->next = new_node;
}

t_env	*parsing_env(char **env)
{
	t_env	*env_list;
	int		i;

	env_list = new_env(env[0]);
	if (env_list == NULL)
		return (NULL);
	i = 1;
	while (env[i] != NULL)
	{
		add_env_back(&env_list, env[i]);
		i++;
	}
	return (env_list);
}
