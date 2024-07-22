/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:59 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/22 16:36:13 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	change_value_env(t_env *env, char *oldpwd, char *pwd)
{
	while (env)
	{
		if (strncmp(env->key_word, "OLDPWD", 6) == 0)
		{
			printf("OLDPWD: %s\n" , oldpwd);
			printf("---- info antes: %s\n", env->info);
			free(env->info);
			env->info = ft_strdup(oldpwd);
			printf("----info depois: %s\n", env->info);
		}
		if (strncmp(env->key_word, "PWD", 3) == 0)
		{
			printf("PWD: %s\n" , pwd);
			printf("---- info antes: %s\n", env->info);
			free(env->info);
			env->info = ft_strdup(pwd);
			printf("----info depois: %s\n", env->info);
		}
		env = env->next;
	}
	return (true);
}

char	*get_env_node(t_env *env, char *str)
{
	while (env)
	{
		if (strncmp(str, env->key_word, strlen(str)) == 0)
		{
			return (env->info);
		}
		env = env->next;
	}
	return (NULL);
}

void	home_dir(t_env *env)
{
	char	*home;
	char	*old_pwd;

	old_pwd = getcwd(NULL,0);
	home = get_env_node(env, "HOME");
	if (home == NULL)
	{
		error_msg("HOME NOT FOUND");
		exit	(EXIT_FAILURE);
	}
	if (chdir(home) == -1)
	{
		error_msg("HOME NOT FOUND");
		exit	(EXIT_FAILURE);
	}
	change_value_env(env, old_pwd, home);
}

void	ft_cd(t_parser *data, t_data *info)
{

	if (data->cmd[1] && data->cmd[2] != NULL)
	{
		error_msg("Too many arguments");
		return ;
	}
	if (data->cmd[1] == NULL || data->cmd[1][0] == '~')
	{
		home_dir(info->env);
		return ;
	}
	if (data->cmd[1][0] == '-')
	{
		home_dir(info->env);
		pwd(data);
	}
	else
	{
		if (access(data->cmd[1], F_OK) != 0)
		{
			printf("chdir = %d\n", chdir(data->cmd[1]));
			printf("access = %d\n", access("Documents", F_OK));
			if (chdir(data->cmd[1]) != 0)
			{
				printf("No such File or Directory\n");
				return ;
			}
		}
	}
// testar a existencia do arquivo com access pq ele pode nao existir qnd nao tem o caminho
// nem sempre vai conseguir acessar 
	// printf("o que esta recebendo %s, %s\n", data->cmd[0], data->cmd[1]);
}
