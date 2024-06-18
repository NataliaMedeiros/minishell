/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/18 13:53:29 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (int argc, char **argv)
{
	char	*prompt_entry;
	
	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd(2, "There is too much arguments");
		ft_putendl_fd(2, "\tExecute only \033[31m./minishell\033[0m");
		exit (EXIT_FAILURE);
	}
	// if (signal(SIGINT, &sighandler) == SIG_ERR) // sighangler eh uma outra funcao que vai modificar o valor de uma variavel de true pra false
	// { // como testar se for um SIG_ERR?
	// 	return (EXIT_FAILURE);
	// }
	while (1) // nao funciona encerrar com um sinal... precisa ser infinito
	{
		prompt_entry = readline("[minishell]> ");
		add_history(prompt_entry);
		if (input_checker(prompt_entry) == true)
		//lexing ou parsing
			printf("data: %s\n", prompt_entry);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
