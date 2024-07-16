/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temporary_functions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:10 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/12 15:19:34 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	print_struct(t_parser *head)
{
	int	i;

	i = 1;
	while (head != NULL)
	{
		printf("flag %d\n", head->flag);
		printf("\033[31mstruct[%d]:\n\033[0m", i);
		if (head->cmd != NULL)
			print_array(head->cmd);
		printf("\033[31moutfile: \033[0m%s\n", head->outfile ? head->outfile : "None");
		printf("\033[31minfile: \033[0m%s\n", head->infile ? head->infile : "None" ); // isso eh proibido pela norminette
		head = head->pipe;
		i++;
	}
}

void	print_env(t_env *env)
{
	while (env->next != NULL)
	{
		printf("key word: %s\nInfo:%s\n", env->key_word, env->info);
		env = env->next;
	}
}
