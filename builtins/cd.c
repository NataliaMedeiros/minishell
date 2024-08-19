/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:59 by edribeir      #+#    #+#                 */
/*   Updated: 2024/08/16 16:40:04 by edribeir      ########   odam.nl         */
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
		return (true);
	else
		return (false);
}

static bool	other_dir(t_parser *data, t_data *info, char *old_pwd)
{
	char	*new_pwd;

	if (access(data->cmd[1], F_OK) == 0)
	{
		if (chdir(data->cmd[1]) != 0)
		{
			ft_putendl_fd(STDOUT_FILENO, "No such File or Directory");
			return (false);
		}
		new_pwd = getcwd(NULL, 0);
		if (change_pwd_value(info->env, old_pwd, new_pwd) == false)
			return (false);
	}
	else
	{
		ft_putendl_fd(STDIN_FILENO, "No Such File or Directory");
		return (false);
	}
	return (true);
}

static char	*home_dir(t_env *env, char *old_pwd)
{
	char	*home;

	home = get_env_node(env, "HOME");
	if (home == NULL)
		return (NULL);
	if (chdir(home) == -1)
	{
		error_msg("HOME NOT FOUND");
		exit (EXIT_FAILURE);
	}
	change_pwd_value(env, old_pwd, home);
	return (home);
}

static void	minus_case(t_data *info, char *old_pwd)
{
	char	*home;

	home = home_dir(info->env, old_pwd);
	if (home != NULL)
		ft_putendl_fd(STDOUT_FILENO, home);
	else
	{
		ft_putendl_fd(STDOUT_FILENO, "HOME Deleted from ENV!");
		return ;
	}
}

void	ft_cd(t_parser *data, t_data *info)
{
	char	*old_pwd;
	char	*home;

	if (data->cmd[1] && data->cmd[2] != NULL)
	{
		error_msg("Too many arguments");
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (data->cmd[1] == NULL || data->cmd[1][0] == '~')
	{
		home = home_dir(info->env, old_pwd);
		if (home == NULL)
			ft_putendl_fd(STDOUT_FILENO, "HOME Deleted from ENV");
		return ;
	}
	else if (data->cmd[1][0] == '-')
		minus_case(info, old_pwd);
	else
	{
		if (other_dir(data, info, old_pwd) == false)
			return ;
	}
}
