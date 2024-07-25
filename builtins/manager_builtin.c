/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:37 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/25 13:50:50 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_fd(t_parser *parser)
{
	int	fd;

	if (parser->outfile == NULL)
		fd = 1;
	else
		fd = parser->fd_outfile;
	return (fd);
}

void	manager_functions(t_parser *parse_data, t_data *data)
{
	if (ft_strncmp(parse_data->cmd[0], "echo", 4) == 0)
		echo_n(parse_data);
	else if (ft_strncmp(parse_data->cmd[0], "pwd", 4) == 0)
		pwd(parse_data);
	else if (ft_strncmp(parse_data->cmd[0], "cd", 2) == 0)
		ft_cd(parse_data, data);
	else if (ft_strncmp(parse_data->cmd[0], "env\0", 4) == 0
		&& parse_data->cmd[1] == NULL)
		env_print(data, parse_data);
	else if(ft_strncmp(parse_data->cmd[0], "unset", 5) == 0)
	{
		if (ft_unset(&data->env, parse_data) != 0)
			return ;
	}
	// ft_free(parse_data);
	// o else vai pra execucao 
	// pode retornar (true or false) e limpar o data aqui para todas as funcoes
}
