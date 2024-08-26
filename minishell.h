/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 11:43:27 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/26 16:32:54 by edribeir      ########   odam.nl         */
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
# include <unistd.h>
# include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

# define RED "\033[31m"
# define RESET "\033[0m"

# define READ 0
# define WRITE 1

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

typedef struct s_execute
{
	int			fd[2];
	int			prev_read;
	int			nb_pipes;
	int			status;
}	t_exec;

typedef struct s_env
{
	char			*key_word;
	char			*info;
	struct s_env	*next;
}					t_env;

typedef struct s_infile
{
	char			*name;
	char			*type;
	struct s_infile	*next;
}				t_infile;

typedef struct s_parser
{
	char			**cmd;
	bool			flag;
	int				fd_outfile;
	char			*outfile;
	int				fd_infile;
	t_infile		*infile;
	struct s_parser	*pipe;
}					t_parser;

typedef struct s_data
{
	char			*cmd_line;
	char			**cmd_table;
	char			**path;
	char			**envp;
	struct s_env	*env;
	t_parser		*parser;
}					t_data;

/* parser */
int			parser(t_data *data);
int			nb_commands(char *cmd_line);
int			pipe_counter(t_parser *parser);

/* parser_heredoc */
int			handle_heredoc(t_parser **parser, t_data data);

/* parser utils */
int			nb_commands(char *cmd_line);
char		**split_cmds(t_data data);
char		*get_cmd(char const *s, unsigned int start, size_t len);

/* free_utils */
void		free_array(int counter, char **cmd);
void		free_env(t_env **env);

/* temporary_functions*/
void		print_struct(t_parser	*head);
void		print_array(char **array);
void		print_env(t_env *env);

/* struct_utils */
t_parser	*new_struct(void);
void		free_parsing(t_parser **parser);

/* parser_fill_cmd */
int			fill_cmd(t_parser **parser, t_data data, int i);

/* utils */
void		error_msg(char *msg);
void		error_msg_with_free(char *msg, char **array);

/* env */
t_env		*parse_env(char **env);

/* heredoc_dollarsign*/
char		*handle_dollar_sign(char *line, t_data data);

// Builtin functions
bool		is_builtin(t_parser *parse_data, t_data *data);
void		echo_n(t_parser *data, int fd);
void		pwd(int fd);
void		ft_cd(t_parser *data, t_data *info);
void		env_print(t_data *data, t_parser *parse, int fd);
void		ft_unset(t_env **env, t_parser *parser);
void		ft_export(t_env **env, t_parser *parser);

// UTILS
bool		has_flags(char *arg, t_parser **parser);
char		*get_env_node(t_env *env, char *str);
void		cleanup(t_data data);

/*parser_remove utils.c*/
char		*remove_quotes(char *limiter);
char		*remove_flags(char *arg);

/*handle file*/
int			handle_files(t_data data, t_parser **parser, int i, bool	start_with_redirection);

bool		has_quotes(char *arg);

/*check input*/
bool		is_input_valid(char *cmd);

// Execution
int			ft_execute(t_data *data);
char		*cmd_path_checker(t_data *data, t_parser *parser);
void		free_split(char **array);
int			one_cmd(t_data *data, char *path);
int			pipeline(t_data *data, t_parser *parser, int nb_pipes);

// Signal
void	set_signals(void);


int	handle_outfile(t_data data, t_parser **parser, int i, bool start_with_redirection);
int	handle_infile(t_data data, t_parser **parser, int i, bool start_with_redirection);
int	handle_files(t_data data, t_parser **parser, int i, bool	start_with_redirection);
char **split_redirection_first(char *cmd);

#endif
