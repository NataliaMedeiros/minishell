/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:56:25 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/13 16:39:49 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*new_struct(void)
{
	t_parser	*new_element;

	new_element = malloc(sizeof(t_parser));
	if (new_element == NULL)
		return (NULL);
	new_element->cmd = NULL;
	new_element->flag = false;
	new_element->infile = NULL;
	new_element->outfile = NULL;
	new_element->fd_infile = -2;
	new_element->fd_outfile = -2;
	new_element->pipe = NULL;
	return (new_element);
}

int	pipe_counter(t_parser *parser)
{
	t_parser	*temp;
	int			counter;

	counter = -1;
	temp = parser;
	while (temp)
	{
		counter++;
		temp = temp->pipe;
	}
	return (counter);
}
