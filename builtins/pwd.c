/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:45 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/18 12:13:27 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_parser *parser)
{
	char	*path;
	int		fd;

	fd = change_fd(parser);
	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		ft_putendl_fd(fd, path);
		free(path);
	}
	// pode ter um retorno qnd for unset? or um check?
}
