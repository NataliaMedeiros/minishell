/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:34:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/23 16:43:35 by edribeir      ########   odam.nl         */
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

int	ft_unset(t_env *env, t_parser *parser)
{
	char	*str;
	t_env	*exc_node;
	t_env	*temp;

	temp = env;
	str = parser->cmd[1];
	if (str == NULL)
	{
		printf("FIZ ND\n");
		return (0);
	}
	while (temp)
	{
		if (ft_strncmp(temp->key_word, str, ft_strlen(str)) == 0)
		{
			exc_node = temp->next;
			temp->next = temp->next->next;
			printf("deleting: %s\n", exc_node->key_word);
			// free(exc_node->key_word);
			// free(exc_node->info);
			// free(exc_node);
			return (0);
		}
		temp = temp->next;
	}
	printf("Nao achei ngm\n");
	return (0);
}