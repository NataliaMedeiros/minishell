/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:59 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/18 18:02:04 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*get_env_node(t_env *env, char *str)
// {
// 	while (env)
// 	{
// 		if (strcmp(str, env->key_word) == 0)
// 			return (env->info);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

// void	home_dir(t_env *env, char *str)
// {
// 	char *home;
// }

void	ft_cd(t_parser *data)
{
	char	*cwd;
	// t_env	*head;

	if (data->cmd[2] != NULL)
	{
		error_msg("Too many arguments");
		return ;
	}
	if (data->cmd[1] == NULL || data->cmd[1][0] == '~')
	{
		printf("Dudita\n");
		// go home env local
		return ;
	}
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	printf("o que esta recebendo %s, %s\n", data->cmd[0], data->cmd[1]);
}
