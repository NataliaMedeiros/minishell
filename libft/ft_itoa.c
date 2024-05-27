/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:17:49 by nmedeiro          #+#    #+#             */
/*   Updated: 2024/04/14 19:44:52 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*new_n;
	int			len;
	long int	nb;

	nb = n;
	len = intlen(n);
	new_n = malloc((len + 1) * sizeof(char));
	if (new_n == NULL)
		return (NULL);
	new_n[len] = '\0';
	if (nb < 0)
	{
		new_n[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		new_n[0] = 0 + '0';
	while (nb > 0)
	{
		len--;
		new_n[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (new_n);
}
