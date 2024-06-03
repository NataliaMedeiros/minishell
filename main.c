/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/05/31 10:20:34 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*input;

	if (argc != 1 && argv)
		printf("too much argments\n");
	while (1)
	{
		input = readline("[minishell]: ");
		add_history(input);
		printf("input = %s\n", input);
		parser(input);
	}
	if (input != NULL)
		free(input);
	return (0);
}
