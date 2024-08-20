/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:34:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/19 15:39:27 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_env_node(t_env *previous, t_env *current, t_env **env)
{
	t_env	*tmp;

	if (previous == NULL)
		*env = current->next;
	else
		previous->next = current->next;
	tmp = current;
	current = current->next;
	free(tmp->key_word);
	free(tmp->info);
	free(tmp);
}

void	ft_unset(t_env **env, t_parser *parser)
{
	char	*str;
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	current = *env;
	if (parser->cmd[1] == NULL)
		return ;
	str = ft_strcharjoin(parser->cmd[1], '=');
	// if (str == NULL)
	// 	return (error_msg("UNEXPECT ERROR"), 1);
	// todo a errormsg with exit
	while (current != NULL)
	{
		if (ft_strncmp(current->key_word, str, ft_strlen(str)) == 0)
		{
			delete_env_node(previous, current, env);
			free(str);
			return ;
		}
		previous = current;
		current = current->next;
	}
	free(str);
}
