#include "../minishell.h"

void	echo_n(t_parser *data)
{
	if (ft_strncmp(data->cmd[0], "echo", 4) == 0)
	{
		if (data->flag == true)
			ft_putstr_fd(data->cmd[1], 1);
		else
			ft_putendl_fd(1, data->cmd[1]);
	}
	// adicionar free para armazenamento da estrutura ?
}