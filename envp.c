/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 17:01:16 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/03 17:01:17 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*check_path(char *cmd, char **envp)
{
	int		i;
	char	*execute;
	char	**path;
	char	*part_path;

	i = 0;
	path = ft_split(ft_find_path(envp), ':');
	if (path == NULL)
	{
		ft_putendl_fd(2, "\033[0;33m\tNot ENV, Unexpected error\033[0m");
		exit (EXIT_FAILURE);
	}
	while (path[i])
	{
		part_path = ft_strjoin(path[i], "/");
		execute = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(execute, F_OK | X_OK) == 0)
			return (/*free_split(path),*/ execute);
		free(execute);
		i++;
	}
	//free_split(path);
	return (NULL);
}
