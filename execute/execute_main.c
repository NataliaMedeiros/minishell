/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 11:38:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/16 16:28:48 by edribeir      ########   odam.nl         */
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
			one_cmd(data, path);
		}
	}
	else if (nb_pipes >= 1)
	{
		pipeline(data, data->parser, nb_pipes);
		// if (pipeline(data, path, data->parser) == 1)
		// 	error_msg("error piping");
	}
	// if (data->parser->infile->name)
	// 	unlink(data->parser->infile->name); // this will be in the cleanup function in the main
	return (0);
}
