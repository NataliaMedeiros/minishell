/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/17 15:58:05 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/17 16:05:21 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	env_node_checker_sign(t_env **env, char *keyword, char *info)
{
	t_env	*temp;
	char	**new_k;

	temp = (*env);
	new_k = ft_split(keyword, '=');
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key_word, new_k[0], ft_strlen(new_k[0])) == 0)
		{
			if (info != NULL)
			{
				free(temp->key_word);
				temp->key_word = ft_strcharjoin(new_k[0], '=');
				free(temp->info);
				temp->info = ft_strdup(info);
			}
			free_split(new_k);
			return (true);
		}
		temp = temp->next;
	}
	free_split(new_k);
	return (false);
}

bool	env_node_checker(t_env **env, char *keyword, char *info)
{
	t_env	*temp;

	temp = (*env);
	if (env_node_checker_sign(env, keyword, info) == true)
		return (true);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key_word, keyword, sizeof(keyword)) == 0)
		{
			if (info != NULL)
			{
				free(temp->info);
				temp->info = ft_strdup(info);
			}
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}

void	keyword_with_info(char *cmd, t_env **env, t_data *data)
{
	char	*keyword;
	char	*info;
	int		position;
	char	*temp;

	temp = cmd;
	position = ft_strchr_pos(cmd, '=');
	info = ft_strchr(temp, '=') + 1;
	keyword = malloc(position + 2 * sizeof(char));
	if (keyword == NULL)
	{
		data->exit_code = 1;
		return ;
	}
	ft_strlcpy(keyword, cmd, position + 2);
	if (env_node_checker(env, keyword, info) == false)
	{
		add_node_env(env, keyword, info);
	}
	if (keyword != NULL)
		free(keyword);
}
