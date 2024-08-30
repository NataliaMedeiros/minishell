/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:32:48 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/30 14:33:19 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	exit_with_msg(char *str, int exit_nb)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(exit_nb);
}
