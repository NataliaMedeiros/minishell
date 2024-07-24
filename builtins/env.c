/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 14:16:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/24 16:38:09 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_print(t_data *data, t_parser *parse)
{
	t_env	*head;
	int		fd;

	if (ft_strncmp(parse->cmd[0], "env\0", 4) == 0
		&& parse->cmd[1] != NULL)
	{
		error_msg("Not such a file or directory");
		// exit (127);
	}
	fd = change_fd(parse);
	head = data->env;
	while (head != NULL)
	{
		ft_putstr_fd(head->key_word, fd);
		ft_putendl_fd(fd, head->info);
		head = head->next;
	}
}
