/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_nl.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/29 14:36:52 by natalia       #+#    #+#                 */
/*   Updated: 2024/04/29 14:37:20 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_nl(char *str)
{
	if (str == NULL)
		str = "(null)";
	write (1, str, ft_strlen(str));
	write (1, "\n", 1);
	return (ft_strlen(str));
}
