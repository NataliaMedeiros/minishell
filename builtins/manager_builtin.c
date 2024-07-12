/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manager_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:04:37 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/12 16:29:06 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manager_functions(t_parser *data)
{
	echo_n(data);
	pwd(data);
	ft_free(data);
	// pode retornar (true or false) e limpar o data aqui para todas as funcoes
}
