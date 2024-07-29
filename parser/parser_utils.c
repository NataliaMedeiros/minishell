/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 20:54:38 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/07/29 12:16:24 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nb_commands(char *cmd_line)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '|' || cmd_line[i] == '>' || cmd_line[i] == '<')
		{
			count += 2;
			if (cmd_line[i + 1] == '>' || cmd_line[i + 1] == '<')
				i += 1;
		}
		i++;
	}
	return (count);
}

char	**split_cmds(t_data data)
{
	int		nb_args;
	int		counter;
	int		i;
	int		start;
	char	**cmd;

	nb_args = nb_commands(data.cmd_line);
	cmd = ft_calloc((nb_args + 1), sizeof(char *));
	if (cmd == NULL)
		return (NULL);
	counter = 0;
	i = 0;
	while (counter < nb_args)
	{
		start = i;
		while (data.cmd_line[i] != '\0' && data.cmd_line[i] != '|'
			&& data.cmd_line[i] != '>' && data.cmd_line[i] != '<')
			i++;
		cmd[counter] = ft_substr_modified(data.cmd_line, start, (i - start));
		printf("cmd[%d]: %s\n", counter, cmd[counter]);
		if (cmd[counter] == NULL)
			return (free_array(counter, cmd), NULL);
		counter++;
		start = i;
		if (counter == nb_args)
			break ;
		if (data.cmd_line[i] == '>' || data.cmd_line[i] == '<')
			i++;
		cmd[counter] = ft_substr(data.cmd_line, start, (i + 1 - start));
		if (cmd[counter] == NULL)
			return (free_array(counter, cmd), NULL);
		counter++;
		i++;
	}
	cmd[counter] = NULL;
	return (cmd);
}

/*this substring was modified to remove space on the beginning*/
char	*ft_substr_modified(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[start] == ' ')
		start++;
	if (ft_strlen(s) <= len)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) == 1 || start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	substring = ft_calloc(len + 1, sizeof(char));
	if (substring == NULL)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		if (s[start] == ' ' && s[start + 1] == '\0')
			return (substring);
		else if (s[start] == ' ' && (s[start + 1] == '>'
				|| s[start + 1] == '<' || s[start + 1] == '|'))
			return (substring);
		substring[i] = s[start];
		i++;
		start++;
	}
	return (substring);
}
