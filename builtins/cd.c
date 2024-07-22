/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:59 by edribeir      #+#    #+#                 */
/*   Updated: 2024/07/22 18:15:15 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	change_value_env(t_env *env, char *oldpwd, char *pwd)
{
	while (env)
	{
		if (strncmp(env->key_word, "OLDPWD", 6) != 0
			|| strncmp(env->key_word, "PWD", 3) != 0)
			return (false);
		if (strncmp(env->key_word, "OLDPWD", 6) == 0)
		{
			free(env->info);
			env->info = ft_strdup(oldpwd);
		}
		if (strncmp(env->key_word, "PWD", 3) == 0)
		{
			free(env->info);
			env->info = ft_strdup(pwd);
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
			return (env->info);
		env = env->next;
	}
	return (NULL);
}

bool	other_dir(t_parser *data, t_data *info, char *old_pwd)
{
	char	*new_pwd;

	if (access(data->cmd[1], F_OK) == 0)
	{
		if (chdir(data->cmd[1]) != 0)
		{
			printf("No such File or Directory\n");
			return (false);
		}
		new_pwd = getcwd(NULL, 0);
		if (change_value_env(info->env, old_pwd, new_pwd) == false)
		{
			error_msg("NOT Such directory");
			return (false);
		}
	}
	else
	{
		printf("No Such File or Directory\n");
		return (false);
	}
	return (true);
}

void	home_dir(t_env *env, char *old_pwd)
{
	char	*home;

	home = get_env_node(env, "HOME");
	if (home == NULL)
	{
		error_msg("HOME NOT FOUND");
		exit (EXIT_FAILURE);
	}
	if (chdir(home) == -1)
	{
		error_msg("HOME NOT FOUND");
		exit (EXIT_FAILURE);
	}
	if (change_value_env(env, old_pwd, home) == false)
	{
		error_msg("NOT Such directory");
		exit (EXIT_FAILURE);
	}
}

void	ft_cd(t_parser *data, t_data *info)
{
	char	*old_pwd;

	if (data->cmd[1] && data->cmd[2] != NULL)
	{
		error_msg("Too many arguments");
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (data->cmd[1] == NULL || data->cmd[1][0] == '~')
	{
		home_dir(info->env, old_pwd);
		return ;
	}
	if (data->cmd[1][0] == '-')
	{
		home_dir(info->env, old_pwd);
		pwd(data);
	}
	else
	{
		if (other_dir(data, info, old_pwd) == false)
			return ;
	}
}
