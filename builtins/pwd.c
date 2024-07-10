#include "../minishell.h"

void	pwd(t_parser *data)
{
	char	*path;

	if(ft_strncmp(data->cmd[0], "pwd", 3) == 0)
	{
		path = getcwd(NULL, 0);
		if (path != NULL)
		{
			ft_putendl_fd(1, path);
			free(path);
		}
	}
}