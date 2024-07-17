/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:59 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/17 14:46:27 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_parser *data)
{
	char *str;
	
	if (data->cmd[1] == NULL)
		return ;
	printf("%s\n\n", data->cmd[2]);
	if (data->cmd[2] != NULL)
	{
		error_msg("Too many arguments");
		return ;
	}
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	printf("o que esta recebendo %s, %s\n", data->cmd[0], data->cmd[1]);
}