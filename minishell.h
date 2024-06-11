/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 11:43:27 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/10 13:11:43 by natalia       ########   odam.nl         */
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
	char				*token;
	struct s_cmd_table	*next;
}						t_cmd_table;

typedef struct s_data
{
	char	*command_line;
	char	**cmd;
	char	**token;
	char	**envp;
}			t_data;

/* parser */
t_token		check_token(char *argv);
void		parser(t_data **data);
char		*check_path(char *cmd, char **envp);
int			nb_commands(char *cmd_line);

/*t_command*/
t_command	*new_command(char *command);
void		add_command_back(t_command **head, char *content);
int			has_quotes(char *argv);
char		*remove_spaces(char *argv);
t_command	*initialize_commands(char *argv);
t_command	*last_node(t_command *lst);

/* ft_adapted_split */
char	**ft_split_adp(char const *s, char const *separators);

#endif
