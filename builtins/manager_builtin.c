#include "../minishell.h"

void	manager_functions(t_parser *data, char **env)
{
	echo_n(data, env);
	pwd(data);
	// pode retornar (true or false) e limpar o data aqui para todas as funcoes
}