/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 17:17:35 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/04 15:25:36 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long	ft_atoi_long(char *str, long nb)
{
	long		i;
	long		sign;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if ((str[i] >= 48 && str[i] <= 57))
			nb = (nb * 10) + (str[i] - 48);
		else
			return (-1);
		if (nb > LONG_MAX)
			return (-1);
		i++;
	}
	if (nb < 0)
		return (-1);
	return ((long)(sign * nb));
}

void	ft_exit(t_data **data, t_parser *parser)
{
	long long	exit_nb;

	if ((ft_strcmp(parser->cmd[0], "exit") == 0) && parser->cmd[1] == NULL)
	{
		(*data)->exit_code = 0;
		ft_putendl_fd(STDERR_FILENO, "exit");
		exit((*data)->exit_code);
	}
	if (parser->cmd[2] != NULL)
	{
		(*data)->exit_code = 1;
		ft_putendl_fd(STDERR_FILENO, "exit");
		ft_putendl_fd(STDERR_FILENO, "minishel: exit: to many arguments");
	}
	else
	{
		exit_nb = ft_atoi_long(parser->cmd[1], 0);
		if (exit_nb == -1)
			exit(exit_nb);
		exit_nb %= 256;
		(*data)->exit_code = exit_nb;
		ft_putendl_fd(STDERR_FILENO, "exit");
		exit((*data)->exit_code);
	}
}
