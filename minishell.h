/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 11:43:27 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/16 17:25:56 by nmedeiro      ########   odam.nl         */
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
# define YEL "\033[0;33m"
# define RESET "\033[0m"

# define READ 0
# define WRITE 1

# define PARENT 1
# define CHILD 2
# define HEREDOC 3

typedef struct s_execute
{
	int			fd[2];
	pid_t		pid_child;
	int			prev_read;
	int			nb_pipes;
	int			i;
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

/* parser_heredoc */
void		handle_heredoc(t_parser **parser, t_data *data);
char		*find_limiter(t_parser **parser);

/* parser utils */
int			nb_commands(char *cmd_line);
char		**split_cmds(t_data data);
char		*get_cmd(char const *s, int unsigned start, size_t len);

/* free_utils */
void		free_array(int counter, char **cmd);
void		free_env(t_env **env);

/* temporary_functions*/
void		print_struct(t_parser	*head);
void		print_array(char **array);
void		print_env(t_env *env);

/* struct_utils */
t_parser	*new_struct(void);
void		free_parser(t_parser **parser);
int			pipe_counter(t_parser *parser);

/* parser_fill_cmd */
int			fill_cmd(t_parser **parser, t_data data, int i, bool *has_pipe);

/* utils */
void		error_msg(char *msg);
void		error_msg_with_free(char *msg, char **array);

/* env */
t_env		*parse_env(char **env);

/* heredoc_dollarsign*/
char		*handle_dollar_sign(char *line, t_data data);
char		*get_var(char *line, int start, t_data data);

// Builtin functions
bool		is_builtin(t_parser *parse_data, t_data *data);
void		echo_n(t_parser *parse, int fd, t_data *data);
void		ft_pwd(int fd, t_parser *parser, t_data *data);
void		ft_cd(t_parser *data, t_data *info);
bool		is_multiples_arg(t_parser *parser, t_data *data);
void		env_print(t_data *data, t_parser *parse, int fd);
void		ft_unset(t_env **env, t_parser *parser, t_data *data);
void		ft_export(t_env **env, t_parser *parser, int fd, t_data *data);
void		export_sorting(t_env **env, int fd);
void		keyword_with_info(char *cmd, t_env **env, t_data *data);
void		add_node_env(t_env **env, char *var_name, char *var_value);
bool		env_node_checker(t_env **env, char *keyword, char *info);
void		ft_exit(t_data *data, t_parser *parser);

// UTILS
bool		has_flags(char *arg, t_parser **parser);
char		*get_env_node(t_env *env, char *str);
void		cleanup(t_data *data);
void		minus_one_verificator(t_parser **parser);

/*parser_remove utils.c*/
char		*remove_quotes(char *limiter);
char		*remove_flags(char *arg);

/*handle file*/
int			handle_files(t_data data, t_parser **parser, int i, bool *has_pipe);
int			handle_infile(t_data data, t_parser **parser, int i,
				bool start_redirection);

bool		has_quotes(char *arg);

/*check input*/
bool		is_input_valid(char *cmd);

// Execution
int			ft_execute(t_data *data);
char		*cmd_path_checker(t_data *data, t_parser *parser);
void		free_split(char **array);
int			one_cmd(t_data *data, char *path);
int			pipeline(t_data *data, t_parser *parser, int nb_pipes);
int			first_cmd(int *fd, t_parser *temp);
int			middle_cmd(t_parser *temp, t_exec *exec);
int			last_cmd(t_parser *temp, t_exec *exec);
void		clean_helper(t_data *data, char *path);
void		exit_status_helper(t_data *data, int status);
void		ft_waiting(t_exec exec);

// Signal
void		handle_signals(int proc);

int			handle_outfile(t_data data, t_parser **parser, int i,
				bool start_with_redirection);
char		**split_redirection_first(char *cmd);

void		exit_with_msg(char *str, int exit_nb);

int			fill_parser(t_data	data, t_parser	**parser);

bool		return_substring(const char *s, int start, bool has_double_quotes);

void		exec_infile(t_parser **parser, t_data *data);

char		*get_var(char *line, int start, t_data data);

bool		has_no_arg(char *cmd);
void		free_infile(t_infile *infile);
void		handle_fd_infile(t_data **data);
void		sig_heredoc(int signum);
int			fill_echo_cmd(t_parser	**parser, t_data data, int i);
char		*replace_dollar_sign(char *l, t_data data, char *new_line);

#endif
