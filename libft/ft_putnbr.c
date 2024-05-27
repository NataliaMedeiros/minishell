/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/29 11:51:58 by natalia       #+#    #+#                 */
/*   Updated: 2024/04/30 16:40:42 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int nb)
{
	char	*nb_char;
	int		len;

	nb_char = ft_itoa(nb);
	len = ft_putstr(nb_char);
	free(nb_char);
	return (len);
}
