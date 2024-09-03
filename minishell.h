/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 11:43:27 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/03 11:44:19 by natalia       ########   odam.nl         */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <stdlib.h>
# include <limits.h>

# define RED "\033[31m"
# define RESET "\033[0m"

# define READ 0
# define WRITE 1

# define PARENT 1
# define CHILD 2
# define HEREDOC 3

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
	int				max_node;
	bool			printed;
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
	int				exit_code;
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
int			handle_heredoc(t_parser **parser, t_data *data);

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
void		echo_n(t_parser *parse, int fd, t_data *data);
void		pwd(int fd);
void		ft_cd(t_parser *data, t_data *info);
void		env_print(t_data *data, t_parser *parse, int fd);
void		ft_unset(t_env **env, t_parser *parser);
void		ft_export(t_env **env, t_parser *parser, int fd);
void		export_print(t_env **env_sort, int fd);
void		export_sorting(t_env **env);

// UTILS
bool		has_flags(char *arg, t_parser **parser);
char		*get_env_node(t_env *env, char *str);
void		cleanup(t_data data);
void		minus_one_verificator(t_parser **parser);

/*parser_remove utils.c*/
char		*remove_quotes(char *limiter);
char		*remove_flags(char *arg);

/*handle file*/
int			handle_files(t_data data, t_parser **parser, int i,
				bool start_with_redirection);

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
void		handle_signals(int proc);


int			handle_outfile(t_data data, t_parser **parser, int i,
				bool start_with_redirection);
int			handle_infile(t_data data, t_parser **parser, int i,
				bool start_with_redirection);
int			handle_files(t_data data, t_parser **parser, int i,
				bool start_with_redirection);
char		**split_redirection_first(char *cmd);

void		exit_with_msg(char *str, int exit_nb);
void		minus_one_verificator(t_parser **parser);

int			fill_parser(t_data	data, t_parser	**parser);

bool		return_substring(const char *s, int start, bool has_double_quotes);

void		exec_infile(t_parser **parser, t_data *data);

void		ft_exit(t_data **data, t_parser *parser);

#endif
