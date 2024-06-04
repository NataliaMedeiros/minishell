/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 11:43:27 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/04 16:42:12 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_token
{
	PIPE,
	WORDS,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
	AND,
} t_token;

typedef struct s_command
{
	char			*command;
	t_token			token;
	struct s_command	*next;
}					t_command;

typedef struct s_cmd_table
{
	char				*cmd;
	t_token				token;
	struct s_cmd_table	*next;
}						t_cmd_table;

/* parser */
t_token		check_token(char *argv);
t_command	*new_command(char *command);
t_command	*last_command(t_command *lst);
void		add_command_back(t_command **head, char *content);
void		parser(char *argv, char **envp);
char		*check_path(char *cmd, char **envp);

#endif
