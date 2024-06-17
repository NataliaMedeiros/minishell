/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/17 17:32:14 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		data->command_line = readline("[minishell]: "); //testar usando point
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
