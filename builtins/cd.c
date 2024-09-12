/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:59 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/10 13:43:36 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	change_pwd_value(t_env *env, char *oldpwd, char *pwd)
{
	int		verificator;
	t_env	*temp;

	verificator = 0;
	temp = env;
	while (temp)
	{
		if (ft_strncmp(env->key_word, "OLDPWD", 6) == 0)
		{
			free(env->info);
			env->info = ft_strdup(oldpwd);
			verificator = 3;
		}
		else if (ft_strncmp(env->key_word, "PWD", 3) == 0)
		{
			free(env->info);
			env->info = ft_strdup(pwd);
			verificator = verificator + 4;
		}
		temp = temp->next;
	}
	if (verificator == 7)
		return (free(oldpwd), true);
	else
		return (free(oldpwd), false);
}

static bool	other_dir(t_parser *data, t_data *info, char *old_pwd)
{
	char	*new_pwd;

	if (access(data->cmd[1], F_OK) == 0)
	{
		if (chdir(data->cmd[1]) != 0)
		{
			if (opendir(data->cmd[1]) == NULL)
			{
				perror("cd");
				info->exit_code = 1;
				return (free(old_pwd), false);
			}
		}
		new_pwd = getcwd(NULL, 0);
		if (change_pwd_value(info->env, old_pwd, new_pwd) == false)
			return (free(new_pwd), false);
	}
	else
	{
		perror("cd");
		return (free(old_pwd), info->exit_code = 1, false);
	}
	return (free(old_pwd), true);
}

static char	*home_dir(t_env *env, char *old_pwd)
{
	char	*home;

	home = get_env_node(env, "HOME");
	if (home == NULL)
		return (NULL);
	if (chdir(home) == -1)
	{
		return (NULL);
	}
	change_pwd_value(env, old_pwd, home);
	return (home);
}

static void	minus_case(t_data *info)
{
	char	*old_pwd;

	old_pwd = get_env_node(info->env, "OLDPWD");
	if (old_pwd == NULL)
	{
		error_msg("OLDPWD not found");
		info->exit_code = 1;
		return ;
	}
	if (chdir(old_pwd) == -1)
	{
		info->exit_code = 1;
		return ;
	}
	else
	{
		ft_putendl_fd(STDOUT_FILENO, old_pwd);
		return ;
	}
}

void	ft_cd(t_parser *data, t_data *info)
{
	char	*old_pwd;
	char	*home;

	if (data->cmd[1] && data->cmd[2] != NULL)
	{
		ft_putendl_fd(STDERR_FILENO, "Too many arguments");
		info->exit_code = 1;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (data->cmd[1] == NULL || data->cmd[1][0] == '~')
	{
		home = home_dir(info->env, old_pwd);
		if (home == NULL)
			ft_putendl_fd(STDOUT_FILENO, "HOME Deleted from ENV");
		info->exit_code = 1;
		return ;
	}
	else if (data->cmd[1][0] == '-')
		minus_case(info);
	else
	{
		if (other_dir(data, info, old_pwd) == false)
			return ;
	}
}
