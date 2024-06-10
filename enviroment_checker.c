#include "minishell.h"

char	*check_path(char **cmd, char **envp)
{
	int		i;
	char	*execute;
	char	**path;
	char	*part_path;

	i = 0;
	path = ft_split(ft_find_path(envp), ':');
	if (path == NULL)
	{
		ft_putendl_fd("\033[0;33m\tNot ENV, Unexpected error\033[0m", 2);
		exit (EXIT_FAILURE);
	}
	while (path[i])
	{
		part_path = ft_strjoin(path[i], "/");
		execute = ft_strjoin(part_path, cmd[0]);
		free(part_path);
		if (access(execute, F_OK | X_OK) == 0)
			return (free_split(path), execute);
		free(execute);
		i++;
	}
	free_split(path);
	return (NULL);
}

char	*ft_find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// t_data	create_command_path(char **argv, char **envp, t_data data)
// {
// 	data.cmd1 = ft_split(argv[2], ' ');
// 	if (data.cmd1[0] == NULL)
// 		exit_print_error(3, data);
// 	if (access(argv[2], F_OK | X_OK) == 0)
// 		data.path_cmd1 = ft_strdup(argv[2]);
// 	else
// 		data.path_cmd1 = check_path(data.cmd1, envp);
// 	data.cmd2 = ft_split(argv[3], ' ');
// 	if (data.cmd2[0] == NULL)
// 		exit_print_error(3, data);
// 	if (access(argv[3], F_OK | X_OK) == 0)
// 		data.path_cmd2 = ft_strdup(argv[3]);
// 	else
// 		data.path_cmd2 = check_path(data.cmd2, envp);
// 	return (data);
// }

// revisar essa funcao, possibilidade para funcoes infinitas?