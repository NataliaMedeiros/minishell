/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 14:16:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/18 16:16:03 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_print(t_data *data)
{
	t_env	*head;

	head = data->env->next;
	while(head != NULL)
	{
		printf("%s%s\n", head->key_word, head->info);
		head = head->next;
	}
}
