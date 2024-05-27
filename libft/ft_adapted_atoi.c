/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_adapted_atoi.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 18:02:40 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/04/30 14:29:05 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_adapted_atoi(const char *nptr)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	if (nptr[i] == '-')
		return (-1);
	if (nptr[i] == '+')
		return (-2);
	while (nptr[i] != '\0')
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			number = number * 10 + (nptr[i] - '0');
		else
			return (-2);
		i++;
	}
	return (number);
}
