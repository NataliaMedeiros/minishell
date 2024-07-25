/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:34:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/25 13:30:34 by edribeir      ########   odam.nl         */
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

// t_env	*previous;
// 	t_env	*current;
// 	t_env	*tmp;

// 	previous = NULL;
// 	tmp = NULL;
// 	current = *env;
// 	while (current != NULL)
// 	{
// 		if (ft_strncmp(current->key_word, str, ft_strlen(str)) == 0)
// 		{
// 			if (previous == NULL)
// 				*env = current->next;
// 			else
// 				previous->next = current->next;
// 			tmp = current;
// 			current = current->next;
// 			free(tmp->key_word);
// 			free(tmp->info);
// 			free(tmp);
// 		}
// 		else
// 		{
// 			previous = current;
// 			current = current->next;
// 		}
// 	}


// void	delete_node(t_env *env, t_env *next_node)
// {
// 	env = next_node->next;
// 	free(next_node->key_word);
// 	free(next_node->info);
// 	free(next_node);
// }

// void delete_node(t_env **env, t_env *delete) {
//     if (*env == NULL || delete == NULL) {
//         return;
//     }

//     t_env *temp = *env;
    
//     if ((*env) == delete) {
//         (*env) = delete->next; 
//     // } else {
//     //     while (temp != NULL && temp->next != delete) {
//     //         temp = temp->next;
//     //     }
//     //     if (temp != NULL) {
//     //         temp->next = delete->next; 
//     //     }
//     }

//     free(delete->key_word);
//     free(delete->info);
	
//     free(delete);
// }

// void delete_node(t_env **env, t_env *delete) {
//     if ((*env) == NULL || delete == NULL) {
//         return;
//     }

//     if (((*env)) == delete)
//         ((*env)) = delete->next;
// 	else
// 	{
// 		printf("VALUE ENV NEXT %s\n", (*env)->next->key_word);
//         if ((*env)->next != NULL) 
//             (*env)->next = delete->next;
//     }

//     free(delete->key_word);
//     free(delete->info);
//     free(delete);
// }



void test(t_env **env) {
	if(env == NULL)
		return;
	t_env *tmp = (*env)->next;
	free((*env)->info);
	free((*env)->key_word);
	free((*env));
	*env = tmp;
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
	t_env	*previous;
	t_env	*current;
	t_env	*tmp;

	previous = NULL;
	tmp = NULL;
	current = *env;
	str = ft_strcharjoin(parser->cmd[1], '=');
	if (str == NULL)
		return (error_msg("UNEXPECT ERROR"), 1);
	while (current != NULL)
	{
		if (ft_strncmp(current->key_word, str, ft_strlen(str)) == 0)
		{
			if (previous == NULL)
				*env = current->next;
			else
				previous->next = current->next;
			tmp = current;
			current = current->next;
			free(tmp->key_word);
			free(tmp->info);
			free(tmp);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	printf("Nao achei ngm\n");
	return (0);
}



	// while (current)
	// {
	// 	// printf("---- AQUI:%s\n", current->key_word);
	// 	if (ft_strncmp(current->key_word, str, ft_strlen(str)) == 0)
	// 	{
	// 		// printf("test: %s\n", str);
	// 		// *env = (*env)->next;
	// 		// free((*env)->info);
	// 		// free((*env)->key_word);
	// 		// free(*env);
	// 		delete_node(previous, current);
	// 		printf("----------------------------------------------------------\n");
	// 		// print_test(*env);
	// 		return (0);
	// 	}
	// 	// if (ft_strncmp(current->next->key_word, str, ft_strlen(str)) == 0)
	// 	// {
	// 	// 	printf("deleting: %s\n", current->next->key_word);
	// 	// 	delete_node(current, current->next);
	// 	// 	return (0);
	// 	// }
	// 	*previous = current;
	// 	current = current->next;
	// }