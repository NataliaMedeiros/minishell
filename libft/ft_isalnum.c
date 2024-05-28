/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 18:21:02 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/05/28 11:20:26 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	This function also could be write on this way:
		return (ft_isalpha(c) || ft_isdigit(c));
*/
#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
