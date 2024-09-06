/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:42:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/05 12:41:39 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	env_node_checker(t_env **env, char *kw, char *info, t_data *d)
{
	t_env	*temp;

	temp = (*env);
	if (kw == NULL)
		return (error_msg("strjoin Error"), d->exit_code = 1, true);
	if (ft_isalpha(kw[0]) == 0)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(kw, STDERR_FILENO);
		return (error_msg(" : not valid"), free(kw), d->exit_code = 1, true);
	}
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key_word, kw, sizeof(kw)) == 0)
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
	free(var_name);
}

void	ft_export(t_env **env, t_parser *parser, int fd, t_data *data)
{
	char	*keyword;
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
			if (ft_strchr(current_cmd[i], '=') != NULL)
				keyword_with_info(current_cmd[i], env, data);
			else
			{
				keyword = ft_strdup(current_cmd[i]);
				if (env_node_checker(env, keyword, NULL, data) == false)
					add_node_env(env, keyword, NULL);
			}
			i++;
		}
	}
}
