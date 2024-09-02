/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:42:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/02 13:40:14 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	env_node_checker(t_env **env, char *keyword, char *info)
{
	t_env	*temp;

	temp = (*env);
	if (keyword == NULL)
		return (error_msg("strjoin Error"), true);
	if (ft_isalpha(keyword[0]) == 0)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(keyword, STDERR_FILENO);
		return (error_msg(" : not a valid identifier"), free(keyword), true);
	}
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

static void	add_node_env(t_env **env, char *var_name, char *var_value)
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

void	keyword_with_info(char *cmd, t_env **env)
{
	char	**array;
	char	*keyword;

	array = ft_split(cmd, '=');
	if (array != NULL)
	{
		keyword = ft_strcharjoin(array[0], '=');
		if (env_node_checker(env, keyword, array[1]) == false)
		{
			add_node_env(env, keyword, array[1]);
			free_split(array);
		}
	}
	else
		error_msg("Split Error");
}

void	ft_export(t_env **env, t_parser *parser, int fd)
{
	char	*keyword;
	int		i;
	char	**current_cmd;

	
	if (parser->cmd[1] == NULL)
	{
		// export_print(env, fd);
		export_sorting(env);
		printf("SORT ME\n");
		// int j = ft_strcmp((*env)->key_word ,(*env)->next->key_word);
		// // int j = (*env)->key_word - (*env)->next->key_word;
		// printf("%i esse eh o valor do j esse eh o fd %i\n", j, fd);
		// printf("%s primeira  %s segunda", (*env)->key_word ,(*env)->next->key_word);
	}
	else
	{
				export_print(env, fd);
		i = 1;
		current_cmd = parser->cmd;
		while (current_cmd[i] != NULL)
		{
			if (ft_strchr(current_cmd[i], '=') != NULL)
				keyword_with_info(current_cmd[i], env);
			else
			{
				keyword = ft_strcharjoin(current_cmd[i], '=');
				if (env_node_checker(env, keyword, NULL) == false)
					add_node_env(env, keyword, NULL);
			}
			i++;
		}
	}
}
