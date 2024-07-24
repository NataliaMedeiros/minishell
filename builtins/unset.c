/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:34:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/24 16:41:54 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// deleta a key relacionada dentro do ambiente, precisa de um argumento relacionado a uma key
// sem a key/argumento valido, nao faz nada

// bool	change_value_env(t_env *env, char *str)
// {
// 	while (env)
// 	{
// 		if (ft_strncmp(env->key_word, str, ft_strlen(str)) == 0)
// 		{
// 			free(env->info);
// 			env->info = ft_strdup(str);
// 			return (true);
// 		}
// 		env = env->next;
// 	}
// 	return (false);
// }




void	delete_node(t_env *env, t_env *next_node)
{
	env = next_node->next;
	free(next_node->key_word);
	free(next_node->info);
	// free(next_node);
}

// void delete_node(t_env *env, t_env *delete) {
//     if (env == NULL || delete == NULL) {
//         return;
//     }

//     t_env *temp = env;
    
//     if (env == delete) {
//         env = delete->next; 
//     } else {
//         while (temp != NULL && temp->next != delete) {
//             temp = temp->next;
//         }
//         if (temp != NULL) {
//             temp->next = delete->next; 
//         }
//     }

//     free(delete->key_word);
//     free(delete->info);
	
//     // free(delete);
// }


void test(t_env *env) {
	if(env == NULL)
		return;
	t_env *tmp = env->next;
	free(env->info);
	free(env->key_word);
	// free(env);
	env = tmp;
}

void print_test(t_env *env) {
	t_env *tmp = env;
	while(tmp) {
		printf("testing: key: %s, info: %s\n", tmp->key_word, tmp->info);
		tmp = tmp->next;
	}
}

// int	ft_unset(t_env *env, t_parser *parser)
// {
// 	char	*str;
// 	// t_env	*temp;

// 	str = ft_strcharjoin(parser->cmd[1], '=');
// 	if (str == NULL)
// 	{
// 		error_msg("UNEXPECT ERROR");
// 		return (1);
// 	}
// 	while (env->next != NULL)
// 	{
// 		printf("---- AQUI:%s\n", env->key_word);
// 		if (ft_strncmp(env->key_word, str, ft_strlen(str)) == 0)
// 		{
// 			t_env *tmp = env;
// 			// env = env->next;
// 			// free(tmp->info);
// 			// free(tmp->key_word);
// 			// free(tmp);
			
// 			// print_test(env);
// 			// printf("pointer in unset: %p\n", env);
// 			// test(env);
// 			// printf("pointer in unset after: %p\n", env);
// 			// env = env->next;
			
// 			// printf("------------------------------------------------\n");
// 			// print_test(env);
// 			// printf("SOCORRO DEUS\n");
// 			// temp = env;
// 			// // temp->next = NULL;
// 			// env = env->next;
// 			// free(temp->key_word);
// 			// free(temp->info);
// 			// // free(temp);
// 			return (0);
// 		}
// 		if (ft_strncmp(env->next->key_word, str, ft_strlen(str)) == 0)
// 		{
// 			printf("deleting: %s\n", env->next->key_word);
// 			delete_node(env, env->next);
// 			return (0);
// 		}
// 		env = env->next;
// 	}
// 	printf("Nao achei ngm\n");
// 	return (0);
// }

int	ft_unset(t_env **env, t_parser *parser)
{
	char	*str;
	// t_env	*temp;

	str = ft_strcharjoin(parser->cmd[1], '=');
	if (str == NULL)
	{
		error_msg("UNEXPECT ERROR");
		return (1);
	}
	// t_env *delete = NULL;
	t_env *current = *env;
	
	while (current)
	{
		// printf("---- AQUI:%s\n", current->key_word);
		if (ft_strncmp(current->key_word, str, ft_strlen(str)) == 0)
		{
			*env = (*env)->next;
			// print_test(env);
			return 0;
		}
		// if (ft_strncmp(env->next->key_word, str, ft_strlen(str)) == 0)
		// {
		// 	printf("deleting: %s\n", env->next->key_word);
		// 	delete = env;
		// 	break;
		// }
		current = current->next;
	}
	// if (delete)
	// 	delete_node(*env, delete);
	// print_test(env);
	// printf("-----------------------------------------------------------------\n");
	// print_test(env);
	// printf("Nao achei ngm\n");
	return (0);
}
