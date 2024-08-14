/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:54:38 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/08/14 16:25:56 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nb_commands(char *cmd_line)
{
	int		i;
	int		count;
	bool	has_double_quotes;

	i = 0;
	count = 1;
	has_double_quotes = false;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '"')
			has_double_quotes = !has_double_quotes;
		if ((cmd_line[i] == '|' || cmd_line[i] == '>' || cmd_line[i] == '<')
			&& has_double_quotes == false)
		{
			count += 2;
			if (cmd_line[i + 1] == '>' || cmd_line[i + 1] == '<')
				i += 1;
		}
		i++;
	}
	return (count);
}

bool	is_operator_or_null(char c)
{
	return (c == '\0' || c == '|' || c == '>' || c == '<');
}

/*this functions find the position where the cmd ends*/
int	find_position(t_data data, int i)
{
	bool	has_double_quotes;

	has_double_quotes = false;
	if (is_operator_or_null(data.cmd_line[i]))
		i++;
	else
	{
		while (!is_operator_or_null(data.cmd_line[i + 1])
			|| has_double_quotes == true)
		{
			if (data.cmd_line[i] == '"')
				has_double_quotes = !has_double_quotes;
			i++;
		}
	}
	return (i);
}

/*This function split the cmds*/
char	**split_cmds(t_data data)
{
	char	**cmd;
	int		nb_args;
	int		counter;
	int		i;
	int		start;

	nb_args = nb_commands(data.cmd_line);
	counter = 0;
	i = 0;
	cmd = ft_calloc(nb_args, sizeof(char *));
	if (cmd == NULL)
		return (NULL);
	while (counter < nb_args - 1 || data.cmd_line[i] != '\0')
	{
		start = i;
		i = find_position(data, i);
		cmd[counter] = get_cmd(data.cmd_line, start,
				(i + 1 - start));
		counter++;
		i++;
	}
	cmd[counter] = NULL;
	return (cmd);
}

int	check_len(const char *s, int start, size_t len)
{
	if (ft_strlen(s) <= len)
		return(ft_strlen(s) - start);
	if (ft_strlen(s) == 1 || start >= (int)ft_strlen(s))
		return(0);
	else if (ft_strlen(s) - start < len)
		return(ft_strlen(s) - start);
	return (len);
}

int	remove_space_at_begging(const char *s, int start)
{
	while (s[start] == ' ')
		start++;
	return (start);
}

bool	return_substring(const char *s, int start, bool has_double_quotes)
{
	if (s[start] == ' ' && s[start + 1] == '\0')
		return (true);
	else if ((s[start] == ' ' && has_double_quotes == false)
			&& (s[start + 1] == '>'|| s[start + 1] == '<'
			|| s[start + 1] == '|'))
		return (true);
	else if (s[start] == ' ' && is_operator_or_null(s[start - 1]) == 1
			&& ft_isalpha(s[start + 1]) == 1 && has_double_quotes == false)
		return (true);
	return (false);
}

/*this substring was modified to remove space on the beginning*/
char	*get_cmd(char const *s, int unsigned start, size_t len)
{
	char	*substring;
	size_t	i;
	bool	has_double_quotes;

	i = 0;
	if (!s)
		return (NULL);
	start = remove_space_at_begging(s, start);
	len = check_len(s, start, len);
	substring = ft_calloc(len + 1, sizeof(char));
	if (substring == NULL)
		return (NULL);
	has_double_quotes = false;
	while (i < len && start < ft_strlen(s))
	{
		if (s[start] == '"')
				has_double_quotes = !has_double_quotes;
		if (return_substring(s, start,
				has_double_quotes) == true)
			return (substring);
		substring[i] = s[start];
		i++;
		start++;
	}
	return (substring);
}
