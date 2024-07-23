/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:34:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/23 20:24:55 by edribeir      ########   odam.nl         */
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
	env->next = next_node->next;
	free(next_node->key_word);
	free(next_node->info);
	free(next_node);
}

int	ft_unset(t_env *env, t_parser *parser)
{
	char	*str;

	str = parser->cmd[1];
	if (str == NULL)
	{
		printf("FIZ ND\n");
		return (0);
	}
	while (env->next != NULL)
	{
		if (ft_strncmp(env->next->key_word, str, ft_strlen(str)) == 0)
		{
			delete_node(env, env->next);
			printf("deleting: %s\n", env->key_word);
			return (0);
		}
		env = env->next;
	}
	printf("Nao achei ngm\n");
	return (0);
}