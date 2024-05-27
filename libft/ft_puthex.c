/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_puthex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 14:11:30 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/04/29 12:12:06 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned int n, const char type)
{
	int				len;
	char			*str_n;
	char			*hex_base;

	if (type == 'x')
		hex_base = "0123456789abcdef";
	else if (type == 'X')
		hex_base = "0123456789ABCDEF";
	if (n == 0)
		return (ft_putchar('0'));
	else
	{
		len = intlen_base(n, 16);
		str_n = ft_calloc(len + 1, sizeof(char));
		while (n > 0)
		{
			str_n[--len] = hex_base[n % 16];
			n /= 16;
		}
		len = ft_putstr(str_n);
		free (str_n);
	}
	return (len);
}

int	ft_putpointer(unsigned long n)
{
	int				len;
	char			*str_n;
	char			*hex_base;

	hex_base = "0123456789abcdef";
	if (n == 0)
		return (ft_putstr("(nil)"));
	else
	{
		len = intlen_base(n, 16) + 2;
		str_n = ft_calloc(len + 1, sizeof(char));
		str_n[0] = '0';
		str_n[1] = 'x';
		while (n > 0)
		{
			str_n[--len] = hex_base[n % 16];
			n /= 16;
		}
		len = ft_putstr(str_n);
		free (str_n);
	}
	return (len);
}
