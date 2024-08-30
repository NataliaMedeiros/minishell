/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_sort_and_print.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 15:40:56 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/30 15:59:07 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_print(t_env **env_sort, int fd)
{
	t_env	*temp;

	temp = *env_sort;
	while (temp != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(temp->key_word, fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(temp->info, fd);
		ft_putendl_fd(fd, "\"");
		temp = temp->next;
	}
}