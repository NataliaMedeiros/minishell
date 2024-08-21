/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 11:38:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/21 13:07:42 by nmedeiro      ########   odam.nl         */
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
			free(path);
			if (exit_nb != 0)
				exit (exit_nb);
		}
	}
	else if (nb_pipes >= 1)
	{
		printf("entramos no multiplos pipes\n");
		exit_nb = pipeline(data, data->parser, nb_pipes);
		if (exit_nb != 0)
			exit (exit_nb);
	}
	// if (data->parser->infile->name)
	// 	unlink(data->parser->infile->name); // this will be in the cleanup function in the main
	return (0);
}
