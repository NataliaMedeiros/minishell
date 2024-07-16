/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/07/16 18:15:21 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	data.env = parsing_env(envp);
	// data.path = parsing_env_path(envp);
	while (1)
	{
		data.command_line = readline("[minishell]: ");
		data.envp = envp;
		add_history(data.command_line);
		if (is_input_valid(data.command_line) == true)
		{
			parser(data);
		}
		// a funcao free pode ser colocada aqui para toda a vez que o programa volta do looping ele eh limpo?
	}
	// rl_clear_history();
	return (0);
}
