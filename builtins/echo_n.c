#include "../minishell.h"

// static bool is_multiple_n(char *cmd)
// {
// 	int	count;

// 	count = 1; // por causa do menos
// 	while(cmd[count] == 'n')
// 		count++;
// 	if(count == 2)
// 		return (false);
// 	else
// 		return (true);
// }

// static char *remove_multiple_n(char *cmd)
// {
// 	char	*only_one_n;
// 	int		i;

// 	i = 0;
// 	only_one_n = malloc()
// 	if (is_multiple_n(cmd) == true)
// 	{
// 		while(cmd[i])
// 		{

// 		}
// 	}
// }

static bool	is_home(char *cmd, char **env)
{
	char	*home;

	if (ft_strncmp(cmd, "$HOME", 5) == 0)
	{
		home = ft_find_path(env, "HOME=");
		ft_putendl_fd(1, home);
		return (true);
	}
	if (ft_strncmp(cmd, "-n $HOME", 5) == 0)
	{
		home = ft_find_path(env, "HOME=");
		printf("%s", home);
		return (true);
	}
	else if (ft_strncmp(cmd, "$home", 5) == 0)
	{
		printf("\n");
		return (true);
	}
	else if (ft_strncmp(cmd, "-n $home", 5) == 0)
		return (true);
	else
		return (false);
}

void	echo_n(t_parser *data, char **env)
{
	if (ft_strncmp(data->cmd[0], "echo", 4) == 0)
	{
		if (ft_strncmp(data->cmd[1], "-n", 2) == 0) // criar com multiplos -n (-nnnnnnnn pq funciona na bash)
		{
			if (is_home(data->cmd[1], env) == false)
				ft_putstr_fd(data->cmd[1] + 3, 1);
		}
		else
		{
			if (is_home(data->cmd[1], env) == false)
				ft_putendl_fd(1, data->cmd[1]);
		}
	}
	// adicionar free para armazenamento da estrutura ?
}