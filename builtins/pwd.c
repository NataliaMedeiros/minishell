/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:45 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/04 16:13:19 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(int fd, t_parser *parser, t_data *data)
{
	char	*path;

	if (parser->cmd[1] != NULL)
	{
		ft_putendl_fd(STDERR_FILENO, "pwd: too many arguments");
		data->exit_code = 1;
		return ;
	}
	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		ft_putendl_fd(fd, path);
		free(path);
	}
}
