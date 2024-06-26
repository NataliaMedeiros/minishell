/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/26 13:13:50 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_input_valid(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if(cmd[i] == '|' || cmd[i] =='>' || cmd[i] == '<')
		{
			if(cmd[i + 1] == '\0')
				return (ft_putendl_fd(2, "Syntax Error"), false);
			i++;
			if (cmd[i] == '|')
				return (ft_putendl_fd(2, "Syntax Error"), false);
			else if ((cmd[i] == '>' && cmd[i - 1] == '<') || (cmd[i] == '<' && cmd[i - 1] == '>'))
				return (ft_putendl_fd(2, "Syntax Error"), false);
			else if (cmd[i] =='>' || cmd[i] == '<')
				i++;
			while (cmd[i] == ' ' && cmd[i] != '\0')
				i++;
			if (cmd[i] == '\0')
				return (ft_putendl_fd(2, "Syntax Error"), false);
			if (cmd[i] == '|' || cmd[i] =='>' || cmd[i] == '<')
				return (ft_putendl_fd(2, "Syntax Error"), false);
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 && argv)
		return (ft_putendl_fd(2, "Too much argments"), 1); //Maybe think in a better message
	while (1)
	{
		data.command_line = readline("[minishell]: ");
		data.envp = envp;
		if (is_input_valid(data.command_line) == true)
		{
			if (parser(data) == 0)
			{
				add_history(data.command_line);
				// rl_on_new_line();
			}
		}
		// printf("---%s---\n", data->command_line);
		// printf("---ls > \n---\n")ls > ;
		// check_path(data->command_line, data->envp);
	}
	return (0);
}
