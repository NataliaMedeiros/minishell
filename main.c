/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/19 14:29:02 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd_line_valid(char *cmd)
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
			else if (cmd[i] =='>' || cmd[i] == '<')
				i++;
			while (cmd[i] == ' ' && cmd[i + 1] != '\0')
				i++;
			if (cmd[i + 1] == '\0')
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
		printf("too much argments\n");
	// data = malloc(sizeof(t_data) * 1);
	// if (data == NULL)
	// 	return (EXIT_FAILURE);
	while (1)
	{
		data.command_line = readline("[minishell]: ");
		if (is_cmd_line_valid(data.command_line) == false)
			return (1);
		// printf("---%s---\n", data->command_line);
		// printf("---ls > \n---\n")ls > ;
		data.envp = envp;
		add_history(data.command_line);
		// parser(&data);
		// check_path(data->command_line, data->envp);
		rl_on_new_line();
	}
	return (0);
}
