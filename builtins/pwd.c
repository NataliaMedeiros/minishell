/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:45 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/08/16 16:05:24 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		ft_putendl_fd(fd, path);
		free(path);
	}
}
