/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 17:15:47 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/09 15:58:01 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_path_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key_word, "PATH", 4) == 0)
			return (temp->info);
		temp = temp->next;
	}
	return (NULL);
}

static char	*check_path(t_data *data, t_parser *parser)
{
	int		i;
	char	*execute;
	char	*part_path;
	char	**path;

	path = ft_split(find_path_env(data->env), ':');
	if (path == NULL)
	{
		ft_putendl_fd(2, YEL"\tPATH DOESN'T EXIST, Unexpected Error"RESET);
		return (NULL);
	}
	i = 0;
	while (path[i])
	{
		part_path = ft_strjoin(path[i], "/");
		execute = ft_strjoin(part_path, parser->cmd[0]);
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

char	*cmd_path_checker(t_data *data, t_parser *parser)
{
	char	*path;

	if (parser->cmd == NULL)
		return (NULL);
	if (access(parser->cmd[0], F_OK | X_OK) == 0)
	{
		path = ft_strdup(parser->cmd[0]);
	}
	else
		path = check_path(data, parser);
	return (path);
}
