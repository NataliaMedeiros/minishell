/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 16:34:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/02 14:10:10 by edribeir      ########   odam.nl         */
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
	char	*cmd;
	int		i;
	char	**current_cmd;
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	if (parser->cmd[1] == NULL)
		return ;
	i = 1;
	current_cmd = parser->cmd;
	while(current_cmd[i] != NULL)
	{
		cmd = ft_strcharjoin(current_cmd[i], '=');
		if(cmd == NULL)
		{
			error_msg("Error strjoin");
			return ;
		}
		current = (*env);
		while (current != NULL)
		{
			if (ft_strncmp(current->key_word, cmd, ft_strlen(cmd)) == 0)
			{
				delete_env_node(previous, current, env);
				break ;
			}
			previous = current;
			current = current->next;
		}
		free(cmd);
		i++;
	}

}
