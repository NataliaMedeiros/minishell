/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_fill_cmd.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmedeiro <nmedeiro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 13:57:08 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/17 14:04:23 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *limiter)
{
	char	*new_limiter;
	int		i;
	int		j;

	new_limiter = ft_calloc(sizeof(char), ft_strlen(limiter) - 1);
	if (new_limiter == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (limiter[i] != '\0')
	{
		if (limiter[i] != '"' && limiter[i] != '\'')
		{
			new_limiter[j] = limiter[i];
			j++;
		}
		i++;
	}
	return (new_limiter);
}

char	*remove_spaces(char *arg)
{
	char	*new_arg;
	int		i;
	int		len;
	int		new_len;

	i = 0;
	len = ft_strlen(arg);
	printf("arg[%d]: %c\n", i, arg[i]);
	while (arg[i] != ' ' && arg[i] != '\0')
		i++;
	i++;
	new_len = len - i + 1;
	new_arg = (char *)malloc(sizeof(char) * new_len);
	if (new_arg == NULL)
		return (NULL);
	ft_strlcpy(new_arg, arg + i, new_len);
	// printf("new arg: %s\n", new_arg);
	return (new_arg);
}

static bool	has_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '"' || arg[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

char	*ft_strtrim_adapted(char const *s1, char const *set)
{
	char	*new_s1;
	int		start;
	int		end;
	int		new_len;

	start = 0;
	end = ft_strlen(s1) -1;
	while (s1[start] != '\0' && s1[start] == set[start])
		start++;
	new_len = end - start + 2;
	new_s1 = (char *)malloc(sizeof(char) * new_len);
	if (new_s1 == NULL)
		return (NULL);
	ft_strlcpy(new_s1, s1 + start, new_len);
	return (new_s1);
}

bool	has_flags(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '-')
			return (true);
		if (arg[i] == '"' || arg[i] == '\'')
			break;
		i++;
	}
	return (false);
}

static int	fill_cmd_mode_echo(t_parser	**parser, t_data data, int i)
{
	char	*temp;
	char	*new_cmd;

	(*parser)->cmd = ft_calloc(sizeof(char *), 3);
	if ((*parser)->cmd == NULL)
		return (1);
	(*parser)->cmd[0] = ft_strdup("echo");
	if ((*parser)->cmd[0] == NULL)
		return (1);
	temp = ft_strtrim_adapted(data.cmd_lst[i], "echo ");
	if (temp == NULL)
		return (1);
	// temp = handle_dollar_sign(temp, data); //comfirmar se tenho que ter essa parte no echo e se esta implementado da maneira correta
	if (has_flags(temp) == true)
		new_cmd = remove_flags(temp);
	else
		new_cmd = strdup(temp);
	free(temp);
	if (has_quotes(new_cmd) == true)
		(*parser)->cmd[1] = remove_quotes(new_cmd);
	else
		(*parser)->cmd[1] = ft_strdup(new_cmd);
	if ((*parser)->cmd[1] == NULL)
			return (1);
	free(new_cmd);
	return (0);
}

int	fill_cmd(t_parser **parser, t_data data, int i)
{
	if (ft_strncmp(data.cmd_lst[i], "echo", 4) == 0)
	{
		if (fill_cmd_mode_echo(parser, data, i) == 1)
			return(error_msg("Failure to fill cmd\n"), 1);
	}
	else
		(*parser)->cmd = ft_split(data.cmd_lst[i], ' ');
	if ((*parser)->cmd == NULL)
		return(error_msg("Failure to fill cmd\n"), 1);
	return (0);
}