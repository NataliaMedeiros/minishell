/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/05 10:27:50 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_prompt(t_data *data)
{
	char	*temp;

	while (1)
	{
		handle_signals(PARENT);
		temp = readline("[minishell]: ");
		if (temp == NULL)
		{
			free(temp);
			if (data->env != NULL)
				free_env(&data->env);
			rl_clear_history();
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		data->cmd_line = ft_strtrim(temp, "\t\n\v\n ");
		free(temp);
		add_history(data->cmd_line);
		if (is_input_valid(data->cmd_line) == true)
		{
			if (data->cmd_line[0] != '\0')
			{
				if (parser(data) == 1)
					return (free(data->cmd_line), cleanup(data), false);
				ft_execute(data);
				cleanup(data);
			}
			else
				free(data->cmd_line);
		}
	}
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
	if (data.env == NULL)
		return (EXIT_FAILURE);
	data.exit_code = 0;
	if (init_prompt(&data) == false)
		return (free_env(&data.env), -1);
	rl_clear_history();
	cleanup(&data);
	if (data.env != NULL)
	{
		free_env(&data.env);
	}
	return (0);
}
