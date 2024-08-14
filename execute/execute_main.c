/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 11:38:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/14 16:05:43 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	pipeline(t_data *data, char *path, t_parser *parser)
// {
// 	int	i = 0;
// 	//int *fd  ||   ||   ||
// 	int	fd[i][2];
// 	int	pd_child1;
// 	int	pd_child2;
// 	int	status;

// 	i = 0;
// 	while (parser->nb_pipes > i)
// 	{
// 		if(pipe(fd[i]) < 0)
// 		{
// 			// precisa fechar os pipes anteriores, se eles tiverem abertos!
// 			error_msg("error pipe");
// 		}
// 		pd_child1 = fork();
// 		if (pd_child1 < 0)
// 			error_msg("Fork error");
// 		if (pd_child1 == 0)
// 		{
// 			//need to close the fd previous and not used, how i will know what to close with child?
// 			dup2(data->parser->fd_infile, STDIN_FILENO);
// 			dup2(fd[i][1], STDOUT_FILENO);
// 			close(data->parser->fd_infile);
// 			close(fd[i][0]);
// 			execve(path, parser->cmd, data->envp);
// 			ft_putstr_fd("Command not found: ", 2);
// 			ft_putendl_fd(2, parser->cmd[0]);
// 			exit (EXIT_FAILURE);
// 		}
// 		pd_child2 = fork();
// 		if (pd_child2 < 0)
// 			error_msg("Fork error");
// 		if (pd_child2 == 0)
// 		{
// 			//need to close the fd previous and not used, how i will now what to close in with child?
// 			// close(fd[0][1]);
// 			dup2(fd[i][0], STDIN_FILENO);
// 			dup2(data->parser->fd_outfile, STDOUT_FILENO);
// 			close(fd[i][1]);
// 			close(data->parser->fd_outfile);
// 			execve(path, parser->cmd, data->envp);
// 			ft_putstr_fd("Command not found: ", 2);
// 			ft_putendl_fd(2, parser->cmd[0]);
// 			exit (127);
// 		}
// 		// waitpid(pd_child1, NULL, 0);
// 		waitpid(pd_child2, &status, 0);
// 		wait(NULL);
// 		i++;
// 	}
// 	close(data->parser->fd_infile);
// 	close(data->parser->fd_outfile);
// 	close(fd[0][1]);
// 	close(fd[i][0]);
// 
// 	// return (0);
// 	// exit(WEXITSTATUS(status));
// }

// char	*find_path_env_pipes(t_env *env)
// {
// 	t_env	*temp;

// 	temp = env;
// 	while (temp)
// 	{
// 		if (ft_strncmp(temp->key_word, "PATH", 4) == 0)
// 			return (temp->info);
// 		temp = temp->next;
// 	}
// 	return (NULL);
// }

// char	*check_path_pipe(t_data *data, t_parser *pipe)
// {
// 	int		i;
// 	char	*execute;
// 	char	**path;
// 	char	*part_path;

// 	i = 0;
// 	path = ft_split(find_path_env_pipes(data->env), ':');
// 	if (path == NULL)
// 	{
// 		// ft_putendl_fd(2, "\033[0;33m\tNot PATH, Unexpected error\033[0m");
// 		// free stuff
// 		return (NULL);
// 		// exit (EXIT_FAILURE);
// 	}
// 	while (path[i])
// 	{
// 		part_path = ft_strjoin(path[i], "/");
// 		execute = ft_strjoin(part_path, pipe->cmd[0]);
// 		free(part_path);
// 		if (access(execute, F_OK | X_OK) == 0)
// 			return (free_split(path), execute);
// 		free(execute);
// 		i++;
// 	}
// 	free_split(path);
// 	return (NULL);
// }


// char	*absolute_path_checker_pipes(t_data *data, t_parser *parse)
// {
// 	char	*path;

// 	if (access(parse->cmd[0], F_OK | X_OK) == 0)
// 		path = ft_strdup(parse->cmd[0]);
// 	else
// 		path = check_path_pipe(data, parse);
// 	return (path);
// }

// void	pipeline(t_data *data, t_parser *parser)
// {
// 	int	i;
// 	//int *fd  ||   ||   ||
// 	int	fd[2];
// 	int	pd_child;
// 	int	status;
// 	t_parser *temp;
// 	char *path;

// 	temp = parser;
// 	i = 0;
// 	path = absolute_path_checker_pipes(data, parser);
// 	// printf("number of pipes: %d <<<<<\n", nb_pipes);
// 	while (temp)
// 	{
// 		// path = absolute_path_checker(data);
// 		if(pipe(fd) < 0)
// 		{
// 			// precisa fechar os pipes anteriores, se eles tiverem abertos!
// 			error_msg("error pipe");
// 		}
// 		// pd_child1 = fork();
// 		// if (pd_child1 < 0)
// 		// 	error_msg("Fork error");
// 		// if (pd_child1 == 0)
// 		// {
// 		// 	//need to close the fd previous and not used, how i will know what to close with child?
// 		// 	dup2(temp->fd_infile, STDIN_FILENO);
// 		// 	dup2(fd[1], STDOUT_FILENO);
// 		// 	close(temp->fd_infile);
// 		// 	close(fd[0]);
// 		// 	execve(path, temp->cmd, data->envp);
// 		// 	ft_putstr_fd("Command not found: ", 2);
// 		// 	ft_putendl_fd(2, temp->cmd[0]);
// 		// 	exit (EXIT_FAILURE);
// 		// }
// 		pd_child = fork();
// 		if (pd_child < 0)
// 			error_msg("Fork error");
// 		if (pd_child == 0)
// 		{
// 			//need to close the fd previous and not used, how i will now what to close in with child?
// 			// close(fd[0][1]);
// 			dup2(fd[0], STDIN_FILENO);
// 			// dup2(temp->fd_outfile, STDOUT_FILENO);
// 			close(fd[1]);
// 			// close(temp->fd_outfile);
// 			execve(path, temp->cmd, data->envp);
// 			ft_putstr_fd("Command not found: ", 2);
// 			ft_putendl_fd(2, temp->cmd[0]);
// 			exit (127);
// 		}
// 		// waitpid(pd_child1, NULL, 0);
// 		waitpid(pd_child, &status, 0);
// 		// wait(NULL);
// 		// printf("passei aqui\n");
// 		temp = temp->pipe;
// 	}
// 	// close(temp->fd_infile);
// 	// close(temp->fd_outfile);
// 	// close(fd[1]);
// 	// close(fd[0]);
	
// 	// return (0);
// 	// exit(WEXITSTATUS(status));
// }

void	one_cmd(t_data *data, char *path, t_parser *parser)
{
	pid_t	pid_child;
	int		status;

	pid_child = fork();
	if (pid_child == -1)
		error_msg("Problem in fork");
	if (pid_child == 0)
	{
		dup2(data->parser->fd_infile, STDIN_FILENO);
		dup2(data->parser->fd_outfile, STDOUT_FILENO);
		close(data->parser->fd_infile);
		close(data->parser->fd_outfile);
		execve(path, parser->cmd, data->envp);
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(2, parser->cmd[0]);
		exit (127);
	}
	waitpid(pid_child, &status, 0);
	// exit(WEXITSTATUS(status));
}

int	ft_execute(t_data *data)
{
	char	*path;
	int		nb_pipes;

	nb_pipes = pipe_counter(data->parser);
	if (nb_pipes == 0)
	{
		if (is_buildin(data->parser, data) == false)
		{
			path = absolute_path_checker(data);
			one_cmd(data, path, data->parser);
		}
	}
	// else if (nb_pipes >= 1)
	// {
	// 	// path = absolute_path_checker(data);
	// 	pipeline(data, data->parser);
	// 	// if (pipeline(data, path, data->parser) == 1)
	// 	// 	error_msg("error piping");
	// }
	return (0);
}
