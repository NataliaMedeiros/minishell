/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 17:15:47 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/01 14:01:48 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path_env(t_env *env)
{
	t_env	*temp; 

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key_word, "PATH",4) == 0)
			return (temp->info);
		temp = temp->next;
	}
	return (NULL);
}

char	*check_path(t_data *data)
{
	int		i;
	char	*execute;
	char	**path;
	char	*part_path;

	i = 0;
	path = ft_split(find_path_env(data->env), ':');
	if (path == NULL)
	{
		// ft_putendl_fd(2, "\033[0;33m\tNot PATH, Unexpected error\033[0m");
		// free stuff
		return (NULL);
		// exit (EXIT_FAILURE);
	}
	while (path[i])
	{
		part_path = ft_strjoin(path[i], "/");
		execute = ft_strjoin(part_path, data->parser->cmd[0]);
		free(part_path);
		if (access(execute, F_OK | X_OK) == 0)
			return (free_split(path), execute);
		free(execute);
		i++;
	}
	free_split(path);
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
char	*absolute_path_checker(t_data *data)
{
	char	*path;

	if (access(data->parser->cmd[0], F_OK | X_OK) == 0)
		path = ft_strdup(data->parser->cmd[0]);
	else
		path = check_path(data);
	return (path);
}
