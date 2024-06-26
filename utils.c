#include "minishell.h"

void	error_msg(char *msg, char **array)
{
	ft_putendl_fd(2, msg);
	if (array != NULL)
		free_array(0, array);
}
