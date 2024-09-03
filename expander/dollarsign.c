/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollarsign.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:05:52 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/03 13:02:17 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* This function replaces the env variable to it's value and return the line
with ALL env variable replaced on the right place when we are working with
heredoc NOTE: On the subject is specified that the env variable just be
replaced ONLY when we have DOUBLE quotes or NO quotes (if we have single
quotes it should NOT be replaced)*/
char	*handle_dollar_sign(char *line, t_data data)
{
	char	*new_line;

	printf("%s\n", line);
	new_line = NULL;
	if (ft_strchr(line, '"') != NULL || ft_strchr(line, '\'') == NULL)
	{
		new_line = replace_dollar_sign(line, new_line, data);
		if (new_line != NULL)
			return (new_line);
	}
	return (line);
}
