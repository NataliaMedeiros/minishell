/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:42:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/30 14:53:08 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// cria uma nova variavel dentro do ambiente, se tiver um = adiciona um valor pra essa variavel
// sem o = seta o valor da variavel pra null
// coloca o env em ordem albetica se for escrito so export sem outro argumento
// mas a variavel q eu criei por ultimo nao fica na ordem alfabetica, ela aparece no final
bool	variable_existence_checker(t_env **env, char *keyword, char *info)
{
	t_env	*temp;

	temp = (*env);
	if (keyword != NULL && ft_isalpha(keyword[0]) == 0)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(keyword, STDERR_FILENO);
		ft_putendl_fd(STDERR_FILENO, ": not a valid identifier");
		return (true);
	}
	while(temp != NULL)
	{
		// printf("\tCurrent temp is: %s%s\n", temp->key_word, temp->info);
		if (ft_strncmp(temp->key_word, keyword, sizeof(keyword)) == 0)
		{
			printf("\tVariable found! Updating value.\n");
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
	t_env		*node;

	node = malloc(1 * sizeof(t_env));
	if (node == NULL)
		return (error_msg("FAIL to ADD Node\n"), NULL);
	// if (var_name == NULL)
	// 	return (NULL);
	node->key_word = ft_strdup(var_name);
	printf("\t\t\tthis is what is inside var_value %s and this is the var_name  %s\n", var_value, var_name);
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
}

void	ft_export(t_env **env, t_parser *parser)
{
	char	**array;
	char	*keyword;
	int		i;
	char	*current_cmd;

	keyword = NULL;
	array = NULL;
	if (parser->cmd[1] == NULL) // export to show env variables
		printf("SORT ME\n");
	else
	{
		i = 1;
		current_cmd = parser->cmd[i];
		while(current_cmd != NULL)
		{
			printf("--- Processing export (%d): %s ---\n", i, current_cmd);
			if (ft_strchr(parser->cmd[i], '=') != NULL) 
			{
				// env var with value
				array = ft_split(parser->cmd[i], '=');
				if (array != NULL)
				{
					keyword = ft_strcharjoin(array[0], '=');
					if(keyword == NULL)
					{
						error_msg("strjoin Error");
						return ;
					}
					printf("Looking for env variable %s\n", keyword);
					if (variable_existence_checker(env, keyword, array[1]) == false)
					{
						// Not found, new env variable
						printf("New environment variable. Creating %s\n", parser->cmd[i]);
						add_node_env(env, keyword, array[1]);
						if (array != NULL)
							free_split(array);
					}
				}
				else {
					// TODO: print error for invalid env var
				}
			}
			else
			{
				keyword = ft_strcharjoin(parser->cmd[i], '=');
				if (keyword == NULL)
				{
					error_msg("strjoin Error");
					return ;
				}
				printf("Looking for env variable into else%s\n", parser->cmd[i]);
				if (variable_existence_checker(env, keyword, NULL) == false)
				{
					// Not found, new env variable
					printf("New environment variable. Creating %s on else\n", keyword);
					add_node_env(env, keyword, NULL);
				}
			}
			i++;
			current_cmd = parser->cmd[i];
			if (keyword != NULL)
				free(keyword);
		}
	}
}
