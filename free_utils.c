/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 13:30:17 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/15 13:30:18 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(int counter, char **cmd)
{
	if (counter == 0)
	{
		while (cmd[counter] != NULL)
		{
			free(cmd[counter]);
			counter++;
		}
	}
	else
	{
		while (counter > 0)
		{
			free(cmd[counter]);
			counter--;
		}
	}
	free(cmd);
}
