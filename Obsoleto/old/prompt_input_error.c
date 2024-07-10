/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt_input_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 11:23:06 by edribeir      #+#    #+#                 */
/*   Updated: 2024/06/18 16:26:31 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	input_checker(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] != '\0')
	{
		if (prompt[i + 1] == '\0' && (prompt[i] == '|'
				|| prompt[i] == '<' || prompt[i] == '>'))
			return (ft_putendl_fd(2, "Syntax Error"), false);
		if (prompt[i] == '<' || prompt[i] == '>')
		{
			if (prompt[i + 1] == '|' || prompt[i + 2] == '|'
				|| prompt[i + 2] == '<' || prompt[i + 2] == '>') // only take care of one space!
				return (ft_putendl_fd(2, "Syntax Error"), false);
		}
		if (prompt[i] == '|')
		{
			if ((prompt[i + 1] == '|' || prompt[i + 1] == '<'
				|| prompt[i + 1] == '>') || (prompt[i + 2] == '|'
				|| prompt[i + 2] == '<' || prompt[i + 2] == '>'))
				return (ft_putendl_fd(2, "Syntax Error"), false);
		}
		// if (prompt[i] == ';' || prompt[i] == '\\')
		// 	return (ft_putendl_fd(2, "Syntax Error"), false);
		i++;
	}
	return (true);
	// o check |      | deveria vir aqui? ou pode ser testado com o access?
}
