/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:38 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/12 14:25:12 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_find_path(char **envp, char *str) //find path -> Duda's function
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	**parsing_env_path(char **envp) //Part of Duda's function
{
	char	**path;

	path = ft_split(ft_find_path(envp, "PATH="), ':');
	if (path == NULL)
		return (error_msg("Unexpected error\n"), NULL);
	return (path);
}
