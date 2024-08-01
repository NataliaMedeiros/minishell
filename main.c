/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/01 13:30:09 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_input_valid(char *cmd) //testar bem essa funcao
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			if (cmd[i + 1] == '\0' || cmd[i + 1] == '|')
				return (error_msg("Syntax Error"), false);
			i++;
			if ((cmd[i] == '>' && cmd[i - 1] == '<')
				|| (cmd[i] == '<' && cmd[i - 1] == '>'))
				return (error_msg("Syntax Error"), false);
			else if (cmd[i] == '>' || cmd[i] == '<')
				i++;
			while (cmd[i] == ' ' && cmd[i] != '\0')
				i++;
			if (cmd[i] == '\0' || cmd[i] == '|' || cmd[i] == '>'
				|| cmd[i] == '<')
				return (error_msg("Syntax Error"), false);
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 && argv)
	{
		error_msg(" Wrong amount of args");
		error_msg("\tExecute only \033[31m./minishell\033[0m");
		return (EXIT_FAILURE);
	}
	data.envp = envp;
	data.env = parsing_env(envp);
	while (1)
	{
		data.cmd_line = readline("[minishell]: ");
		if (data.cmd_line[0] != '\0')
		{
			add_history(data.cmd_line);
			if (is_input_valid(data.cmd_line) == true)
			{
				parser(&data);
				ft_execute(&data);
			}
		}
	}
	// rl_clear_history();
	return (0);
}
