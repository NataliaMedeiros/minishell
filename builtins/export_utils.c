/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 15:40:56 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/05 12:33:18 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	keyword_with_info(char *cmd, t_env **env, t_data *data)
{
	char	**array;
	char	*keyword;

	array = ft_split(cmd, '=');
	if (array != NULL)
	{
		keyword = ft_strcharjoin(array[0], '=');
		if (env_node_checker(env, keyword, array[1], data) == false)
		{
			add_node_env(env, keyword, array[1]);
			free_split(array);
		}
	}
	else
		error_msg("Split Error");
}

static void	export_print(t_env *last_printed, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(last_printed->key_word, fd);
	if (ft_strcmp(last_printed->info, "") != 0)
	{
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(last_printed->info, fd);
		ft_putendl_fd(fd, "\"");
	}
	else
	{
		if (ft_strchr(last_printed->key_word, '=') != 0)
		{
			ft_putstr_fd("\"", fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putendl_fd(fd, "");
	}
}

static int	lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

static t_env	*find_env_to_print(t_env *aux,
	t_env *last_printed, int last_printed_result, int to_print_result)
{
	t_env	*env_to_print;

	env_to_print = NULL;
	while (aux != NULL)
	{
		if (last_printed != NULL)
			last_printed_result = ft_strcmp(aux->key_word,
					last_printed->key_word);
		else
			last_printed_result = 1;
		if (env_to_print != NULL)
			to_print_result = ft_strcmp(aux->key_word, env_to_print->key_word);
		else
			to_print_result = -1;
		if (last_printed_result > 0 && to_print_result < 0)
			env_to_print = aux;
		aux = aux->next;
	}
	return (env_to_print);
}

void	export_sorting(t_env **env, int fd)
{
	int		printed_amount;
	int		last_printed_result;
	int		to_print_result;
	t_env	*aux;
	t_env	*last_printed;

	printed_amount = 0;
	last_printed_result = INT_MIN;
	last_printed = NULL;
	while (printed_amount < lstsize(*env))
	{
		aux = *env;
		to_print_result = INT_MIN;
		last_printed = find_env_to_print(aux,
				last_printed, last_printed_result, to_print_result);
		export_print(last_printed, fd);
		printed_amount++;
	}
}
