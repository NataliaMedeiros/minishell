/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 14:16:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/05 10:37:14 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_print(t_data *data, t_parser *parse, int fd)
{
	t_env	*head;

	if (parse->cmd[1] != NULL)
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(parse->cmd[1], STDERR_FILENO);
		ft_putendl_fd(STDERR_FILENO, " : Not such a file or directory");
		data->exit_code = 127;
		return ;
	}
	head = data->env;
	while (head != NULL)
	{
		ft_putstr_fd(head->key_word, fd);
		ft_putendl_fd(fd, head->info);
		head = head->next;
	}
}
