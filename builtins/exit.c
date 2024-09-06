/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 17:17:35 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/06 11:04:06 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_cleaner(t_data *data)
{
	free_env(&data->env);
	cleanup(data);
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
		exit_cleaner(data);
		exit(data->exit_code);
	}
	exit_nb %= 256;
	data->exit_code = exit_nb;
	ft_putendl_fd(STDERR_FILENO, "exit");
	exit_cleaner(data);
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
		data->exit_code = 2;
		ft_putendl_fd(STDERR_FILENO, "exit");
		ft_putstr_fd("exit : ", STDERR_FILENO);
		ft_putendl_fd(STDERR_FILENO, "numeric argument required");
		exit_cleaner(data);
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
		exit_cleaner(data);
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
