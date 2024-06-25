/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 11:43:27 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/24 17:02:47 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h> //boolean
# include <fcntl.h> //function open
# include <string.h>

typedef enum s_token
{
	PIPE,
	WORDS,
	IN,
	HEREDOC,
	OUT,
	APPEND,
	AND,
}		t_token;

typedef struct s_parser
{
	char	**cmd;
	int		fd_outfile;
	char	*outfile;
	int		fd_infile;
	char	*infile;
	struct s_parser	*pipe;
}			t_parser;

typedef struct s_data
{
	char	*command_line;
	char	**cmd_lst;
	char	**token;
	char	**envp;
}			t_data;

/* parser */
t_token		check_token(char *argv);
int		parser(t_data data);
char		*check_path(char *cmd, char **envp);
int			nb_commands(char *cmd_line);

/*t_command*/
int			has_quotes(char *argv);
char		*remove_spaces(char *argv);

/* ft_adapted_split */
char		**ft_split_adp(char const *s, char const *separators);

#endif
