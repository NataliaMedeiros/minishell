/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/19 14:08:38 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_cmd_line_calid(t_data *data)
{
	int		i;
	char	cmd;

	i = 0;
	while (data->command_line[i] != '\0')
	{
		if (data->command_line[i + 1] == '\0' && (data->command_line[i] == '|'
				|| data->command_line[i] == '<' || data->command_line[i] == '>'))
			return (ft_putendl_fd(2, "Syntax Error"), false);
		cmd = data->command_line[i];
		if (cmd == '|' || cmd =='>' || cmd == '<')
		{
			i++;
			while (data->command_line[i] == ' ' && data->command_line[i + 1] != '\0')
				i++;
			if (data->command_line[i + 1] == '\0')
				return (ft_putendl_fd(2, "Syntax Error"), false);
		}
		if (data->command_line[i] == '<' || data->command_line[i] == '>')
		{
			if (data->command_line[i + 1] == '|' || data->command_line[i + 2] == '|'
				|| data->command_line[i + 2] == '<' || data->command_line[i + 2] == '>') // only take care of one space!
				return (ft_putendl_fd(2, "Syntax Error"), false);
		}
		if (data->command_line[i] == '|')
		{
			if ((data->command_line[i + 1] == '|' || data->command_line[i + 1] == '<'
				|| data->command_line[i + 1] == '>') || (data->command_line[i + 2] == '|'
				|| data->command_line[i + 2] == '<' || data->command_line[i + 2] == '>'))
				return (ft_putendl_fd(2, "Syntax Error"), false);
		}
		// if (prompt[i] == ';' || prompt[i] == '\\')
		// 	return (ft_putendl_fd(2, "Syntax Error"), false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1 && argv)
		printf("too much argments\n");
	data = malloc(sizeof(t_data) * 1);
	if (data == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		data->command_line = readline("[minishell]: ");
		if (is_cmd_line_calid(data) == false)
			return (1);
		printf("---%s---\n", data->command_line);
		printf("---ls > \n---\n");
		data->envp = envp;
		add_history(data->command_line);
		parser(&data);
		check_path(data->command_line, data->envp);
		rl_on_new_line();
	}
	return (0);
}
