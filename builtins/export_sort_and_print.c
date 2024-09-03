/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_sort_and_print.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 15:40:56 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/03 12:55:04 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_print(t_env **env_sort, int fd)
{
	t_env	*temp;

	temp = *env_sort;
	while (temp != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(temp->key_word, fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(temp->info, fd);
		ft_putendl_fd(fd, "\"");
		temp = temp->next;
	}
}

// void add_node_env(t_env **tail, char *keyword, char *info)
// {
// 	t_env	*new_node;

// 	new_node = malloc(1 *sizeof(t_env));
// 	if (new_node == NULL)
// 		return ;
// 	new_node->key_word = keyword;
// 	new_node->info = info;
// 	new_node->next = NULL;
// 	if (*tail != NULL)
// 	{
// 		(*tail)->next = new_node;
// 	}
// 	*tail = new_node;
// }

// t_env **cpy_env(t_env **head)
// {
// 	t_env	*new_head;
// 	t_env	*tail;
// 	t_env	*temp;

// 	temp = (*head);
// 	tail = NULL;
// 	new_head = NULL;
// 	if (*head == NULL)
// 		return (NULL);
// 	while (temp != NULL)
// 	{
// 		if (new_head == NULL)
// 		{
// 				add_node_env(&new_head, temp->key_word, temp->info);
// 				tail = new_head;
// 		} else
// 		{
// 			add_node_env(&tail, temp->key_word, temp->info);
// 		}
// 		temp = temp->next;
// 	}
// 	return (new_head);
// }

// void export_sorting(t_env **env, int fd)
// {
// 	t_env	**env_cpy;
// 	// t_env	*temp;
// 	// int		result;

// 	// temp = (*env);
// 	// while (temp->next != NULL)
// 	// {
// 	// 	result = ft_strcmp(temp->key_word, temp->next->key_word);
// 	// 	printf("this is the result of strcmp %d\n", result);
// 	// 	temp = temp->next;
// 	// }
// 	env_cpy = cpy_env(env);
// 	export_print(env_cpy, fd);
// }