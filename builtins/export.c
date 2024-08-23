/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:42:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/23 16:07:47 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// cria uma nova variavel dentro do ambiente, se tiver um = adiciona um valor pra essa variavel
// sem o = seta o valor da variavel pra null
// coloca o env em ordem albetica se for escrito so export sem outro argumento
// mas a variavel q eu criei por ultimo nao fica na ordem alfabetica, ela aparece no final
static t_env	*create_new_node(t_parser *parser)
{
	t_env	*node;
	char	**array;

	node = malloc(1 * sizeof(t_env));
	if (node == NULL)
		return (error_msg("FAIL to ADD Node\n"), NULL);
	node->key_word = ft_strdup(parser->cmd[1]);
	// case with spaces
	if (ft_strncmp(parser->cmd[2], "=", 1) == 0)
	{
		if(parser->cmd[3] == NULL)
			node->info = 'NULL';
		else
			node->info = ft_strdup(parser->cmd[3]);
	}
	else
	// case withoutspaces
	{
		if (ft_strcmp(parser->cmd[2], "=") == 0)
		{
			array = ft_split(parser->cmd[2], "=");
			if (array == NULL)
				return ;
			node->key_word = ft_strdup(array[0]);
			if (array[1] == NULL)
				node->info = 'NULL';
			else
				node->info = ft_strdup(array[1]);
		}
		else
			node->key_word = 'NULL';
	}
	node->next = NULL;
	return (node);
}

static void	add_node_env(t_env **env, t_parser *parser)
{
	t_env	*temp;
	t_env	*new_node;

	temp = (*env);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	

}

void	ft_export(t_env **env, t_parser *parser)
{
	
}