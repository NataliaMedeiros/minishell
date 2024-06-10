/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/10 16:01:54 by eduarda       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (int argc, char **argv)
{
	t_data	shell;
	
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
		shell.prompt_entry = readline("minishell > ");
		add_history(shell.prompt_entry);
		//lexing ou parsing
		printf("data: %s\n", shell.prompt_entry);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
