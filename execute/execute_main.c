/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 11:38:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/10 12:17:06 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute(t_data *data)
{
	char	*path;
	int		nb_pipes;

	nb_pipes = pipe_counter(data->parser);
	if (nb_pipes == 0)
	{
		if (is_builtin(data->parser, data) == false)
		{
			path = cmd_path_checker(data, data->parser);
			data->exit_code = one_cmd(data, path);
			if (path != NULL)
				free (path);
		}
	}
	else if (nb_pipes >= 1)
	{
		data->exit_code = pipeline(data, data->parser, nb_pipes);
	}
	return (data->exit_code);
}
