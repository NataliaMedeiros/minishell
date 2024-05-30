/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/05/30 14:00:24 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *argv)
{
	char	**tokens;
	int		i;

	tokens = ft_split(argv, ' ');
	i = 0;
	while (tokens[i] != NULL)
	{
		printf("tokens = %s\n", tokens[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*input;

	if (argc != 1 && argv)
		printf("too much argments\n");
	while (1)
	{
		input = readline("[minishell]: ");
		printf("%s\n", input);
		parser(input);
	}
	if (input != NULL)
		free(input);
	return (0);
}
