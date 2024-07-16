/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:37 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/16 18:02:06 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manager_functions(t_parser *parse_data, t_data *data)
{
	// if (ft_strncmp(parse_data->cmd[0], "echo", 4) == 0)
	echo_n(parse_data);
	pwd(parse_data);
	if (ft_strncmp(parse_data->cmd[0], "env\0", 4) == 0 && parse_data->cmd[1] == NULL)
		env_print(data);
	else if(ft_strncmp(parse_data->cmd[0], "env\0", 4) == 0 && parse_data->cmd[1] != NULL)
		error_msg("Not such a file or directory");
	ft_free(parse_data);
	// pode retornar (true or false) e limpar o data aqui para todas as funcoes
}
