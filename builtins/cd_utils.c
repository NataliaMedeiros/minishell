/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 15:07:00 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/13 17:03:39 by edribeir      ########   odam.nl         */
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

bool	is_multiples_arg(t_parser *parser, t_data *data)
{
	if (parser->cmd[1] && parser->cmd[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putendl_fd(STDERR_FILENO, "Too many arguments");
		data->exit_code = 1;
		return (true);
	}
	return (false);
}
