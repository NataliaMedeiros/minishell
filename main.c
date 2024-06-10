/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/10 13:08:26 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*data;

	if (argc != 1 && argv)
		printf("too much argments\n");
	data = malloc(sizeof(t_data) * 1);
	if (data == NULL)
		return (EXIT_FAILURE);
	while (1)
	{
		data->command_line = readline("[minishell]: ");
		data->envp = envp;
		add_history(data->command_line);
		printf("input = %s\n", data->command_line);
		parser(data);
		check_path(data->command_line, data->envp);
		rl_on_new_line();
	}
	if (input != NULL)
		free(input);
	return (0);
}
