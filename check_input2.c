/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/06 16:54:59 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/06 16:57:46 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_no_arg(char *cmd)
{
	if ((cmd[0] == '>' || cmd[0] == '<' || cmd[0] == '|')
		&& (cmd[1] == '>' || cmd[1] == '<' || cmd[1] == '|')
		&& (cmd[2] == '\0'))
		return (false);
	return (true);
}
