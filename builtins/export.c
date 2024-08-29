/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:42:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/29 13:20:09 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// cria uma nova variavel dentro do ambiente, se tiver um = adiciona um valor pra essa variavel
// sem o = seta o valor da variavel pra null
// coloca o env em ordem albetica se for escrito so export sem outro argumento
// mas a variavel q eu criei por ultimo nao fica na ordem alfabetica, ela aparece no final
// static	bool	is_new(t_parser *parser, char *keyword_2, int i)
// {
// 	t_parser	*temp;

// 	temp = parser;
// 	while(temp)
// 	{
// 		if (ft_strncmp(temp->cmd[i], keyword_2, sizeof(keyword_2)) == 0)
// 			return (false);
// 		temp = temp->pipe;
// 	}
// 	return (true);
// }

// static	t_env	*without_spaces_node_creation(t_parser *parser, bool flag)
// {
// 	t_env		*node;
// 	t_env		*node_2;
// 	char		*keyword;
// 	char		*keyword_2;
// 	char		**array;
// 	int 		i;


// 	node_2 = NULL;
// 	array = parser->cmd;
// 	if (flag == false)
// 	{
// 		keyword = ft_strcharjoin(array[1], '=');
// 		node->key_word = keyword;
// 		node->info = ft_strdup("");
// 		printf("%s<<<<<<<<<<<<\n", array[3]);
// 		if (array[3] != NULL)
// 		{
// 			i = 3;
// 			while(array[i] != NULL)
// 			{
// 				keyword_2 = ft_strcharjoin(array[i], '=');
// 				if (is_new(parser, keyword_2, i) == true)
// 				{
// 					if (ft_strncmp(keyword, keyword_2, sizeof(keyword_2)) != 0)
// 					{
// 						printf("Pass here\n");
// 						node_2 = malloc(1 * sizeof(t_env));
// 						if (node_2 == NULL)
// 						return (error_msg("FAIL to ADD Node\n"), NULL);
// 							node_2->key_word = ft_strcharjoin(parser->cmd[3], '=');
// 						node_2->info = ft_strdup("");
// 						node_2->next = NULL;
// 						node->next = node_2;
// 					}
// 				}
// 				free(keyword_2);
// 				i++;
// 			}
// 		}
// 		else
// 				node->next = NULL;
// 			return (node);
// 	}
// 	return (NULL);
// }

static t_env	*create_new_node(t_parser *parser, bool flag)
{
	t_env	*node;
	char	**array;
	char	*keyword;
	// t_parser	*temp;

	printf("%i", flag);
	// temp = parsmer;
	array = NULL;
	node = malloc(1 * sizeof(t_env));
	if (node == NULL)
		return (error_msg("FAIL to ADD Node\n"), NULL);
	// case withoutspaces
	if (parser->cmd[1] != NULL && (ft_strchr(parser->cmd[1], '=') != NULL))
	{
		array = ft_split(parser->cmd[1], '=');
		if (array == NULL)
			return (NULL);
		keyword = ft_strcharjoin(array[0], '=');
		if (keyword == NULL)
			return (NULL);
		node->key_word = keyword;
		if (array[1] == NULL)
			node->info = ft_strdup("");
		else
			node->info = ft_strdup(array[1]);
	}
	// case with spaces
	if (ft_strncmp(parser->cmd[2], "=", 1) == 0)
	{
		// before create again verify if it already exists in the env
		ft_putendl_fd(STDERR_FILENO, "export: `=': not a valid identifier");
	}
	else
	{
		if (parser->cmd[1] != NULL)
		{
			keyword = ft_strcharjoin(parser->cmd[1], '=');
			node->key_word = keyword;
			node->info = ft_strdup("");
		}
	}
	node->next = NULL;
	if (array != NULL)
		free_split(array);
	return (node);
}

static void	add_node_env(t_env **env, t_parser *parser, bool flag)
{
	t_env	*temp;
	t_env	*new_node;

	temp = (*env);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	new_node = create_new_node(parser, flag);
	temp->next = new_node;
}

void	ft_export(t_env **env, t_parser *parser)
{
	t_env	*temp;
	char	**array;
	char	*keyword;
	bool	flag;

	flag = false;
	keyword = NULL;
	temp = (*env);
	if (parser->cmd[1] == NULL)
		printf("SORT ME\n");
	else
	{
		while (temp != NULL)
		{
			// with is numerical cannot be created
			if (parser->cmd[1] != NULL && (ft_strchr(parser->cmd[1], '=') != NULL)) // without space
			{
				array = ft_split(parser->cmd[1], '=');
				if (array == NULL)
					return ;
				keyword = ft_strcharjoin(array[0], '=');
				if (ft_strncmp(temp->key_word, keyword, sizeof(keyword)) == 0)
				{
					free(temp->info);
					if (keyword != NULL && array[1] != NULL)
						temp->info = ft_strdup(array[1]);
					else
						temp->info = ft_strdup("");
					free_split(array);
					free(keyword);
					return	;
				}
				else
				{
					if (array != NULL)
						free_split(array);
					if (keyword != NULL)
						free(keyword);
					add_node_env(env, parser, flag);
					return	;
				}
			}
			else
			{
				// if(ft_strncmp(parser->cmd[2], "=", 1) == 0) // with space
				// {
				// 	keyword = ft_strcharjoin(parser->cmd[1], '=');
				// 	if (ft_strncmp(temp->key_word, keyword, sizeof(keyword)) == 0)
				// 	{
				// 		free(keyword);
				// 		flag = true;
				// 	}
				// }
				add_node_env(env, parser, flag);
				return	;
			}
			temp = temp->next;
		}
	}
}
