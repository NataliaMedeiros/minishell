/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 14:16:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/16 18:03:39 by edribeir      ########   odam.nl         */
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
