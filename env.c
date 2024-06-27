#include "minishell.h"

char	*ft_find_path(char **envp) //find path -> Duda's function
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

char	**parsing_env_path(char **envp) //Part of Duda's function
{
	char	**path;

	path = ft_split(ft_find_path(envp), ':');
	if (path == NULL)
		return(error_msg("Unexpected error\n", NULL), NULL);
	return (path);
}
