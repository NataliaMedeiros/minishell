/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_builtin.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 15:07:00 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/16 16:49:47 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_node(t_env *env, char *str)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(str, temp->key_word, strlen(str)) == 0)
			return (temp->info);
		temp = temp->next;
	}
	return (NULL);
}
