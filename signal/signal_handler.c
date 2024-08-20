/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 14:30:30 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/20 14:34:19 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "../minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>

void	return_prompt(void)
{
	printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(int sig)
{
	return_prompt();
	(void)sig;
}

void	unset_signals(void )
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_term(void)
{
	struct termios	term;

	tcgetattr(fileno(stdin), &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(fileno(stdin), 0, &term);
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	set_term();
}
