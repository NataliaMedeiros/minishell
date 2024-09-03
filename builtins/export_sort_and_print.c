/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_sort_and_print.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/30 15:40:56 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/02 13:39:29 by edribeir      ########   odam.nl         */
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

void export_sorting(t_env **env)
{
	// t_env	**env_sorting;
	t_env	*temp;
	int		test;
	// int		i;

	temp = (*env);
	while(temp->next != NULL)
	{
		test = ft_strcmp(temp->key_word, temp->next->key_word);
		printf("this is the result of strcmp %d\n", test);
		temp = temp->next;
	}
}