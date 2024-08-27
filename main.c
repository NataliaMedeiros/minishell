/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/27 14:07:59 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_prompt(t_data data)
{
	char	*temp;

	while (1)
	{
		// set_signals();
		handle_signals(PARENT);
		temp = readline("[minishell]: ");
		if (temp == NULL)
			exit(EXIT_SUCCESS);
		data.cmd_line = ft_strtrim(temp, "\t\n\v\n ");
		add_history(data.cmd_line);
		//add function to add space where it is needed
		if (is_input_valid(data.cmd_line) == true)
		{
			if (data.cmd_line[0] != '\0')
			{
				if (parser(&data) == 1)
					return (false);
				ft_execute(&data);
				// cleanup(data);
			}
		}
		free(data.cmd_line);
	}
	free(data.cmd_line);
	free(temp);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 && argv)
	{
		error_msg(" Wrong amount of args");
		error_msg("\tExecute only "RED"./minishell"RESET);
		return (EXIT_FAILURE);
	}
	data.envp = envp;
	data.env = parse_env(envp);
	if (init_prompt(data) == false)
		return (free_env(&data.env), -1);
	// rl_clear_history();
	cleanup(data);
	if (data.env != NULL)
	{
		printf("clean 1!\n");
		free_env(&data.env);
	}
	return (0);
}
