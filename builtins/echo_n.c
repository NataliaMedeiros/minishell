#include "../minishell.h"

void echo_n(t_parser *data)
{
		if (ft_strncmp(data->cmd[0], "echo", 4) == 0)
		{
			if (ft_strncmp(data->cmd[1], "-n", 2) == 0)
			{
				ft_putstr_fd(data->cmd[1] + 3, 1);
				// printf("\taqui!\n");
			}
			else
			{
				ft_putendl_fd(1, data->cmd[1]);
				// printf("testando nova linha anterior\n");
			}
		}
		// adicionar free para armazenamento da estrutura ?
}