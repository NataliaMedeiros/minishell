/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:56:25 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/08/07 17:19:53 by nmedeiro      ########   odam.nl         */
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
	new_element->fd_infile = -2; //check if is good initualize
	new_element->fd_outfile = -2; //check if is good initualize
	new_element->nb_pipes = 0;
	new_element->pipe = NULL;
	return (new_element);
}

void	free_parsing(t_parser **parser)
{
	t_parser	*temp;

	while (*parser)
	{
		temp = *parser;
		*parser = (*parser)->pipe;
		free(temp);
	}
	*parser = NULL;
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