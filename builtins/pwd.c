/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:45 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/10 15:04:46 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_parser *data)
{
	char	*path;

	if(ft_strncmp(data->cmd[0], "pwd", 3) == 0)
	{
		path = getcwd(NULL, 0);
		if (path != NULL)
		{
			ft_putendl_fd(1, path);
			free(path);
		}
	}
}