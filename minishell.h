/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 10:47:19 by edribeir      #+#    #+#                 */
/*   Updated: 2024/06/18 14:53:38 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>

// typedef struct s_pipe
// {
// 	char *child2;
// 	// char **path_env;
// 	// char **cmd_array;
// 	// char *outfile;
// 	// char *infile;
// 	// char *heredoc;
// 	t_data child2;
// } t_pipe;

// typedef struct s_data
// {
// 	char **path_env;
// 	char **cmd_array;
// 	char *outfile;
// 	char *infile;
// 	char *heredoc;
// 	t_pipe pipe;
// } t_data;

bool	input_checker(char *prompt);

#endif