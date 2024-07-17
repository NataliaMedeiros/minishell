/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:45 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/17 14:13:21 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		ft_putendl_fd(1, path);
		free(path);
	}
}
