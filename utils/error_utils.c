/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 14:31:31 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/03 12:40:33 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minus_one_verificator(t_parser **parser)
{
	if ((*parser)->fd_infile == -1)
		perror("bash");
}
