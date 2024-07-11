/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 11:43:27 by natalia       #+#    #+#                 */
/*   Updated: 2024/07/11 14:28:55 by edribeir      ########   odam.nl         */
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

typedef enum s_token //nao usado
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
	char			**cmd;
	bool			flag;
	int				fd_outfile;
	char			*outfile;
	int				fd_infile;
	char			*infile;
	struct s_parser	*pipe;
}			t_parser;

typedef struct s_data
{
	char	*command_line;
	char	**cmd_lst;
	char	**token;
	char	**envp;
	char	**path;
}			t_data;

/* parser */
t_token		check_token(char *argv);
int			parser(t_data data);
char		*check_path(char *cmd, char **envp);
int			nb_commands(char *cmd_line);

/*t_command*/
//bool			has_quotes(char *argv);
char		*remove_spaces(char *argv);

/* ft_adapted_split */
char		**ft_split_adp(char const *s, char const *separators);

/* parser_heredoc */
int			handle_heredoc(t_parser **parser, t_data data);

/* parser utils */
int		nb_commands(char *cmd_line);
char	**split_cmds(t_data data);
char	*ft_substr_modified(char const *s, unsigned int start, size_t len);

/* free_utils */
void	free_array(int	counter, char **cmd);

/* temporary_functions*/
void	print_struct(t_parser	*head);
void	print_array(char **array);

/* struct_utils */
t_parser	*new_struct();
void		free_parsing(t_parser **parser);

/* parser_fill_cmd */
int			fill_cmd(t_parser **parser, t_data data, int i);

/* utils */
void		error_msg(char *msg);
void		error_msg_with_free(char *msg, char **array);

/* env */
char		**parsing_env_path(char **envp);

/* heredoc_dollarsign*/
char		*handle_dollar_sign(char *line, t_data data);

// Builtin functions
void	manager_functions(t_parser *data);
void	echo_n(t_parser *data);
void	pwd(t_parser *data);

bool	has_flags(char *arg);

/*parser_remove utils.c*/
char	*remove_quotes(char *limiter);
char	*remove_flags(char *arg);

#endif