/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 17:17:35 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/05 17:25:16 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long	ft_atoi_long(char *str, long nb) // put this on libft
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

static bool	is_numerical(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '-')
		i++;
	while (input[i])
	{
		if (ft_isdigit(input[i]) != 1)
			return (false);
		i++;
	}
	return (true);
}

static void	one_arg(t_data *data, t_parser *parser)
{
	long long	exit_nb;

	exit_nb = ft_atoi_long(parser->cmd[1], 0);
	if (is_numerical(parser->cmd[1]) == false)
	{
		ft_putendl_fd(STDERR_FILENO, "exit");
		ft_putstr_fd("exit : ", STDERR_FILENO);
		ft_putstr_fd(parser->cmd[1], STDERR_FILENO);
		ft_putendl_fd(STDERR_FILENO, ": numeric argument required");
		data->exit_code = 2;
		exit(data->exit_code);
	}
	exit_nb %= 256;
	data->exit_code = exit_nb;
	ft_putendl_fd(STDERR_FILENO, "exit");
	exit(data->exit_code);
}

static void	multiple_arg(t_data *data, t_parser *parser)
{
	int		nb_cmd;
	int		not_numerical;
	char	**array;

	nb_cmd = 0;
	array = parser->cmd;
	not_numerical = 0;
	while (array[nb_cmd])
	{
		if (is_numerical(array[nb_cmd]) == false)
			not_numerical++;
		nb_cmd++;
	}
	if (nb_cmd == not_numerical)
	{
		ft_putendl_fd(STDERR_FILENO, "exit");
		ft_putstr_fd("exit : ", STDERR_FILENO);
		ft_putendl_fd(STDERR_FILENO, "numeric argument required");
		data->exit_code = 2;
		exit(data->exit_code);
	}
	data->exit_code = 1;
	ft_putendl_fd(STDERR_FILENO, "exit");
	ft_putendl_fd(STDERR_FILENO, "minishell: exit: too many arguments");
}

void	ft_exit(t_data *data, t_parser *parser)
{
	if (parser->cmd[1] == NULL)
	{
		data->exit_code = 0;
		ft_putendl_fd(STDERR_FILENO, "exit");
		free_env(&data->env);
		cleanup(data); // create a function that clean stuff for the exit, before exiting ALL CASES!
		exit(data->exit_code);
	}
	if (parser->cmd[2] != NULL)
	{
		multiple_arg(data, parser);
	}
	else
	{
		one_arg(data, parser);
	}
}
