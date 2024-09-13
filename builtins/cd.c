/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/12 12:26:59 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/13 16:58:52 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	change_pwd_value(t_env **env, char *oldpwd, char *pwd)
{
	int		verificator;
	t_env	*temp;

	verificator = 0;
	temp = (*env);
	while (temp)
	{
		if (ft_strncmp(temp->key_word, "OLDPWD", 6) == 0)
		{
			free(temp->info);
			temp->info = ft_strdup(oldpwd);
			verificator = 3;
		}
		else if (ft_strncmp(temp->key_word, "PWD", 3) == 0)
		{
			free(temp->info);
			temp->info = ft_strdup(pwd);
			verificator = verificator + 4;
		}
		temp = temp->next;
	}
	if (verificator == 7)
		return (free(oldpwd), true);
	else
		return (free(oldpwd), false);
}

static bool	other_dir(t_parser *parser, t_data *data, char *old_pwd)
{
	char	*new_pwd;

	if (access(parser->cmd[1], F_OK) == 0)
	{
		if (chdir(parser->cmd[1]) != 0)
		{
			if (opendir(parser->cmd[1]) == NULL)
			{
				perror("cd");
				data->exit_code = 1;
				return (free(old_pwd), false);
			}
		}
		new_pwd = getcwd(NULL, 0);
		if (change_pwd_value(&data->env, old_pwd, new_pwd) == false)
			return (free(new_pwd), false);
		free(new_pwd);
	}
	else
	{
		perror("cd");
		return (free(old_pwd), data->exit_code = 1, false);
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
		return (NULL);
	}
	change_pwd_value(&env, old_pwd, home);
	return (home);
}

static void	minus_case(t_data *data)
{
	char	*old_pwd;

	old_pwd = get_env_node(data->env, "OLDPWD");
	if (old_pwd == NULL)
	{
		error_msg("OLDPWD not found");
		data->exit_code = 1;
		return ;
	}
	if (chdir(old_pwd) == -1)
	{
		data->exit_code = 1;
		return ;
	}
	else
	{
		ft_putendl_fd(STDOUT_FILENO, old_pwd);
		return ;
	}
}

void	ft_cd(t_parser *parser, t_data *data)
{
	char	*old_pwd;
	char	*home;

	if (is_multiples_arg(parser, data) == true)
		return ;
	old_pwd = getcwd(NULL, 0);
	if (parser->cmd[1] == NULL || parser->cmd[1][0] == '~')
	{
		home = home_dir(data->env, old_pwd);
		if (home == NULL)
			ft_putendl_fd(STDOUT_FILENO, "HOME Deleted from ENV");
		data->exit_code = 1;
		return ;
	}
	else if (parser->cmd[1][0] == '-')
	{
		minus_case(data);
		free(old_pwd);
	}
	else
	{
		if (other_dir(parser, data, old_pwd) == false)
			return ;
	}
}
