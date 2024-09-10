/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_files.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 15:10:34 by natalia       #+#    #+#                 */
/*   Updated: 2024/09/09 12:15:38 by nmedeiro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_be_null(char **temp, int nb)
{
	nb--;
	while (nb >= 0)
	{
		temp[nb] = NULL;
		nb--;
	}
}

void	fill_temp(char **temp, int i, char *cmd, int j)
{
	if (j == 0)
	{
		temp[0] = ft_calloc((i + 1), sizeof(char));
		if (temp[0] == NULL)
			return ;
		ft_strlcpy(temp[0], cmd, (i + 1));
	}
	else
	{
		temp[1] = ft_calloc((j - i + 1), sizeof(char));
		if (temp[1] == NULL)
			return ;
		ft_strlcpy(temp[1], cmd + i, (j - i + 1));
	}
}

char	**split_redirection_first(char *cmd)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_calloc(3, sizeof(char *));
	if (temp == NULL)
		return (NULL);
	ft_be_null(temp, 3);
	while (cmd[i] != ' ' && cmd[i] != '\0')
		i++;
	fill_temp(temp, i, cmd, j);
	if (temp[0] == NULL)
		return (free_array(3, temp), NULL);
	j = i;
	while (cmd[j] != '\0')
		j++;
	if (j > i)
		fill_temp(temp, i, cmd, j);
	return (temp);
}

int	handle_files(t_data data, t_parser **parser, int i, bool *has_pipe)
{
	bool	start_with_redirection;

	if (i == 0 || *has_pipe == true || (*parser)->cmd == NULL)
		start_with_redirection = true;
	else
		start_with_redirection = false;
	if (data.cmd_table[i][0] == '>')
	{
		if (handle_outfile(data, parser, i, start_with_redirection) != 0)
			return (error_msg("failure on handle outfile"), 1);
	}
	else if (data.cmd_table[i][0] == '<')
	{
		if (handle_infile(data, parser, i, start_with_redirection) != 0)
			return (error_msg("failure on handle infile"), 1);
	}
	*has_pipe = false;
	return (0);
}
