/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:42:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/29 22:41:25 by eduarda       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// cria uma nova variavel dentro do ambiente, se tiver um = adiciona um valor pra essa variavel
// sem o = seta o valor da variavel pra null
// coloca o env em ordem albetica se for escrito so export sem outro argumento
// mas a variavel q eu criei por ultimo nao fica na ordem alfabetica, ela aparece no final

static t_env	*create_new_env_node(char *var_name, char *var_value)
{
	t_env		*node;

	node = malloc(1 * sizeof(t_env));
	if (node == NULL)
		return (error_msg("FAIL to ADD Node\n"), NULL);
	if (var_name == NULL)
		return (NULL);
	node->key_word = ft_strdup(var_name);
	if (var_value == NULL)
		node->info = ft_strdup("");
	else
		node->info = ft_strdup(var_value);
	node->next = NULL;
	return (node);
}

static void	add_node_env(t_env **env, char *var_name, char *var_value)
{
	t_env	*temp;
	t_env	*new_node;

	new_node = NULL;
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
	t_env	*temp;
	char	**array;
	char	*keyword;
	int		i;
	char	*current_cmd;

	keyword = NULL;
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
				if (array != NULL){
					keyword = ft_strcharjoin(array[0], '=');
					temp = (*env);
					printf("Looking for env variable %s\n", keyword);
					while(temp != NULL)
					{
						printf("\tCurrent temp is: %s%s\n", temp->key_word, temp->info);
						if (ft_strncmp(temp->key_word, keyword, sizeof(keyword)) == 0)
						{
							printf("\tVariable found! Updating value.\n");
							free(temp->info);
							if (keyword != NULL && array[1] != NULL)
								temp->info = ft_strdup(array[1]);
							else
								temp->info = ft_strdup("");
							free_split(array);
							free(keyword);
							break;
						}
						temp = temp->next;
					}
					// Not found, new env variable
					printf("New environment variable. Creating %s\n", parser->cmd[i]);
					add_node_env(env, keyword, array[1]);
					if (array != NULL)
						free_split(array);
					if (keyword != NULL)
						free(keyword);
				}
				else {
					// TODO: print error for invalid env var
				}
			}
			i++;
			current_cmd = parser->cmd[i];
		}
	}
}
