/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 11:38:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/12 12:17:48 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	second_child(t_data *data, int *fd_pipe, char **envp, char *path)
// {
// 	// int	fd_outfile;

// 	// fd_outfile = open(data->outfile, O_CREAT | O_TRUNC | O_RDWR, 0666);
// 	// if (fd_outfile == -1)
// 	// {
// 	// 	free_child(data);
// 	// 	perror("Open Outfile");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	dup2(fd_pipe[0], STDIN_FILENO);
// 	// dup2(data->parser->fd_outfile, STDOUT_FILENO);
// 	close(fd_pipe[1]);
// 	execve(path, &data->parser->cmd[0], envp);
// 	ft_putstr_fd("Command not found: ", 2);
// 	ft_putendl_fd(2, data->parser->cmd[0]);
// 	// free_child(data);
// 	// exit(127);
// }

// void	first_child(t_data *data, int *fd_pipe, char **envp, char *path)
// {
// 	// int	fd_infile;

// 	// fd_infile = open(data->infile, O_RDONLY, 0444);
// 	// if (fd_infile == -1)
// 	// {
// 	// 	free_child(data);
// 	// 	perror("Open Infile");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	// dup2(data->parser->fd_infile, STDIN_FILENO);
// 	dup2(fd_pipe[1], STDOUT_FILENO);
// 	close(fd_pipe[0]);
// 	execve(path, &data->parser->cmd[0], envp);
// 	ft_putstr_fd("Command not found: ", 2);
// 	ft_putendl_fd(2, data->parser->cmd[0]);
// 	// free_child(data);
// 	// exit(EXIT_SUCCESS);
// }

// void	pipex_parent(t_data *data, char **envp, char *path)
// {
// 	int		fd_pipe[2];
// 	pid_t	pid_child;
// 	pid_t	pid_child2;
// 	int		status;

// 	if (pipe(fd_pipe) == -1)
// 		printf("deu erro\n"); // error and free
// 	pid_child = fork();
// 	if (pid_child == -1)
// 		printf("deu erro fork\n");
// 	if (pid_child == 0)
// 		first_child(data, fd_pipe, envp, path);
// 	pid_child2 = fork();
// 	if (pid_child2 == -1)
// 		// exit_print_error(4, data);
// 	if (pid_child2 == 0)
// 		second_child(data, fd_pipe, envp, path);
// 	close(fd_pipe[READ]);
// 	close(fd_pipe[WRITE]);
// 	waitpid(pid_child2, &status, 0);
// 	wait(NULL);
// 	exit(WEXITSTATUS(status));
// }

void	one_cmd(t_data *data, char *path, t_parser *parser)
{
	pid_t	pid_child;
	int		status;

	pid_child = fork();
	if (pid_child == 0)
	{
		dup2(data->parser->fd_outfile, STDOUT_FILENO);
		execve(path, parser->cmd, data->envp);
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(2, parser->cmd[0]);
	}
	waitpid(pid_child, &status, 0);
}

int	ft_execute(t_data *data)
{
	char	*path;

	if (data->parser->nb_pipes == 0)
	{
		if (is_buildin(data->parser, data) == false)
		{
			path = absolute_path_checker(data);
			one_cmd(data, path, data->parser);
		}
	}
	// else if (data->parser->nb_pipes >= 1)
	// {

	// }
	return (0);
}
