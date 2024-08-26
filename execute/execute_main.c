/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 11:38:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/26 16:24:35 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execute(t_data *data)
{
	char	*path;
	int		nb_pipes;
	int		exit_nb;

	nb_pipes = pipe_counter(data->parser);
	if (nb_pipes == 0)
	{
		if (is_builtin(data->parser, data) == false)
		{
			path = cmd_path_checker(data, data->parser);
			exit_nb = one_cmd(data, path);
			if (path != NULL)
				free (path);
			// if (exit_nb != 0)
			// 	exit (exit_nb);
		}
	}
	else if (nb_pipes >= 1)
	{
		printf("entramos no multiplos pipes\n");
		exit_nb = pipeline(data, data->parser, nb_pipes);
		// if (exit_nb != 0)
		// 	exit (exit_nb);
	}
	return (0);
}
