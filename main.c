/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/07 14:27:19 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 && argv)
	{
		error_msg(" Wrong amount of args");
		error_msg("\tExecute only "RED"./minishell"RESET);
		return (EXIT_FAILURE);
	}
	data.envp = envp; // testar
	data.env = parse_env(envp);
	while (1)
	{
		data.cmd_line = readline("[minishell]: ");
		add_history(data.cmd_line);
		if (is_input_valid(data.cmd_line) == true)
		{
			if (data.cmd_line[0] != '\0')
			{
				if (parser(&data) == 1)
					return (free_env(&data.env), -1);
				ft_execute(&data);
			}
		}
	}
	// rl_clear_history();
	return (0);
}
