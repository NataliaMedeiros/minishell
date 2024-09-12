/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:42:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/10 16:44:42 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	env_node_checker(t_env **env, char *keyword, char *info)
{
	t_env	*temp;

	temp = (*env);
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

static t_env	*create_new_env_node(char *var_name, char *var_value)
{
	t_env	*node;

	node = malloc(1 * sizeof(t_env));
	if (node == NULL)
		return (error_msg("FAIL to ADD Node\n"), NULL);
	node->key_word = ft_strdup(var_name);
	if (var_value != NULL)
		node->info = ft_strdup(var_value);
	else
		node->info = ft_strdup("");
	node->next = NULL;
	return (node);
}

void	add_node_env(t_env **env, char *var_name, char *var_value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = (*env);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	new_node = create_new_env_node(var_name, var_value);
	temp->next = new_node;
}

static bool	is_valid(char **current_cmd, int i, t_data *data)
{
	if (ft_isalpha(current_cmd[i][0]) == 0)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(current_cmd[i], STDERR_FILENO);
		error_msg(" : not valid");
		data->exit_code = 1;
		return (false);
	}
	return (true);
}

void	ft_export(t_env **env, t_parser *parser, int fd, t_data *data)
{
	int		i;
	char	**current_cmd;

	if (parser->cmd[1] == NULL)
		export_sorting(env, fd);
	else
	{
		i = 1;
		current_cmd = parser->cmd;
		while (current_cmd[i] != NULL)
		{
			if (is_valid(current_cmd, i, data) == true)
			{
				if (ft_strchr(current_cmd[i], '=') != NULL)
					keyword_with_info(current_cmd[i], env, data);
				else
				{
					if (env_node_checker(env, current_cmd[i], NULL) == false)
						add_node_env(env, current_cmd[i], NULL);
				}
			}
			i++;
		}
	}
}
