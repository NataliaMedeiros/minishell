/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:50:38 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/12 16:27:55 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char *msg)
{
	ft_putendl_fd(2, msg);
}

void	error_msg_with_free(char *msg, char **array)
{
	ft_putendl_fd(2, msg);
	if (array != NULL)
		free_array(0, array);
}
