/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_sort_and_print.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 15:40:56 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/03 13:33:16 by natalia       ########   odam.nl         */
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

// void export_sorting(t_env **env)
// {
// 	// t_env	**env_sorting;
// 	t_env	*copy_env;
// 	t_env	*bla;
// 	t_env	*lala;
// 	int		bigger;

// 	copy_env = (*env);
// 	while(copy_env->next != NULL)
// 	{
// 		bigger = INT_MIN;
// 		bla = (*env);
// 		while(bla != NULL)
// 		{
// 			copy_env->max_node = ft_strcmp(copy_env->key_word, bla->key_word);
// 			// printf("this is the result of strcmp %d\n", temp->max_node);
// 			// printf("temp mim: %d\n", temp->min_node);
// 			if (copy_env->max_node > bigger)
// 			{
// 				printf("---%s\n", copy_env->key_word);
// 				bigger = copy_env->max_node;
// 			}
// 			// printf("temp bigger %d\n", bigger);
// 			bla = bla->next;
// 		}
// 		lala = (*env);
// 		while (lala->next != NULL)
// 		{
// 			if (lala->max_node == bigger)
// 			{
// 				printf("%s%s\n", lala->key_word, lala->info);
// 				break;
// 			}
// 			lala = lala->next;
// 		}
// 		copy_env = copy_env->next;
// 	}
// 	copy_env = (*env);

// 	//-------
// 	// while (temp->next != NULL)
// 	// {
// 	// 	bla = (*env);
// 	// 	while(bla != NULL)
// 	// 	{
// 	// 		if( ft_strcmp(temp->key_word, bla->key_word) == 0)
// 	// 			bla = bla->next;
// 	// 		else if (temp->min_node == bla->min_node)
// 	// 		{
// 	// 			printf("****\n");
// 	// 			printf("key word: %s temp: %f bla: %f\n",temp->key_word, temp->min_node, bla->min_node);
// 	// 			test = ft_strcmp(temp->key_word, bla->key_word);
// 	// 			if (test > temp->min_node)
// 	// 			{
// 	// 				temp->min_node += 0.1;
// 	// 				bla->min_node -= 0.1;
// 	// 			}
// 	// 			else
// 	// 			{
// 	// 				temp->min_node -= 0.1;
// 	// 				bla->min_node += 0.1;
// 	// 			}
// 	// 			printf("this is the result of strcmp %f\n", test);
// 	// 		}
// 	// 		bla = bla->next;
// 	// 	}
// 	// 	temp = temp->next;
// 	// }
// 	// temp = (*env);
// 	// while (temp->next != NULL)
// 	// {
// 	// 	bla = temp->next;
// 	// 	while(bla != NULL)
// 	// 	{
// 	// 		if (temp->min_node == bla->min_node)
// 	// 		{
// 	// 			printf("**ERROR - %s and %s**\n", temp->key_word, bla->key_word);
// 	// 		}
// 	// 		bla = bla->next;
// 	// 	}
// 	// 	temp = temp->next;
// 	// }
// 	// temp = (*env);
// 	// temp->position = 1;
// 	// while (temp->next != NULL)
// 	// {
// 	// 	bla = temp->next;
// 	// 	while(bla != NULL)
// 	// 	{
// 	// 		if (temp->min_node > bla->min_node)
// 	// 			temp->position++;
// 	// 		bla = bla->next;
// 	// 	}
// 	// 	temp = temp->next;
// 	// }
// 	// temp = (*env);
// 	// while (temp->next != NULL)
// 	// {
// 	// 	printf("key word: %s position: %d\n", temp->key_word, temp->position);
// 	// 	temp = temp->next;
// 	// }
// 	// printf("......\n");
// 	// int	bigger = INT_MIN;
// 	// temp = (*env);
// 	// while (temp->next != NULL)
// 	// {
// 	// 	if (temp->position > bigger)
// 	// 		bigger = temp->position;
// 	// 	temp = temp->next;
// 	// }
// 	// printf("bigger: %d\n", bigger);
// }

int	lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void export_sorting(t_env **env)
{
	int printed_amount;
	int last_printed_result;
	int to_print_result;
	t_env *aux;
	t_env *env_to_print;
	t_env *last_printed;

	printed_amount = 0;
	last_printed_result = INT_MIN;
	last_printed = NULL;
	while (printed_amount < lstsize(*env)) // Get total amount of env variables
	{
		aux = *env;
		env_to_print = NULL;
		to_print_result = INT_MIN;
		while (aux != NULL) {
			if (last_printed != NULL)
				last_printed_result = ft_strcmp(aux->key_word, last_printed->key_word);
			else
				last_printed_result = 1;

			if (env_to_print != NULL)
				to_print_result = ft_strcmp(aux->key_word, env_to_print->key_word);
			else
				to_print_result = -1;
			if (last_printed_result > 0 && to_print_result < 0)
				env_to_print = aux;
			aux = aux->next;
		}
		last_printed = env_to_print;
		printf("%s%s\n", last_printed->key_word, last_printed->info);
		printed_amount++;
	}

}
