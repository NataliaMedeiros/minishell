/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 14:30:30 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/28 15:07:29 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "../minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>

// void	return_prompt(void)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	//rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	sigint_handler(int sig)
// {
// 	return_prompt();
// 	(void)sig;
// }

// void	unset_signals(void )
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }

// void	ignore_signals(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	set_term(void)
// {
// 	struct termios	term;

// 	tcgetattr(fileno(stdin), &term);
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(fileno(stdin), 0, &term);
// }

// void	set_signals(void)
// {
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// 	set_term();
// }

static void	sig_parent(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_redisplay();
	}
}

/**
 * @param signum int with signal value
 * @brief Signal handler for the child process.
 * called when the child process receives a SIGINT signal.
 * It simply outputs a newline character to STDOUT_FILENO
*/
static void	sig_child_c(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @param signum int with signal value
 * @brief Signal handler for the child process.
 * called when the child process receives a SIGQUIT signal.
 * It outputs the message "Quit" to STDERR_FILENO.
*/
static void	sig_child_q(int signum)
{
	if (signum == SIGQUIT)
		write(STDERR_FILENO, "Quit\n", 6);
}

/**
 * @param signum The signal number.
 * @brief Signal handler for here_doc (input redirection).
 * called when the here_doc process receives a signal.
 */
static void	sig_hd(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		exit (130);
	}
}

/**
 * @param proc The type of process (PARENT, CHILD, or HERE_DOC).
 * @brief Sets signal handlers for different process types.
 * sets signal handlers for different process types:
 * - For the parent process:
 * SIGINT is handled by `sig_parent`, and SIGQUIT is ignored.
 * - For the child process:
 * SIGINT is handled by `sig_child_c`, and SIGQUIT is handled by `sig_child_q`.
 * - For the here_doc process:
 * SIGINT is handled by `sig_hd`, and SIGQUIT is ignored.
 */
void	handle_signals(int proc)
{
	if (proc == PARENT)
	{
		signal(SIGINT, sig_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	if (proc == CHILD)
	{
		signal(SIGINT, sig_child_c);
		signal(SIGQUIT, sig_child_q);
	}
	if (proc == HEREDOC)
	{
		signal(SIGINT, sig_hd);
		signal(SIGQUIT, SIG_IGN);
	}
}
