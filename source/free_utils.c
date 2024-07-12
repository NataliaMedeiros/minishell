/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:43 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/12 16:29:37 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
void	ft_free(t_parser *parser)
{
	if (parser->cmd != NULL)
		free_array(0, parser->cmd);
}
