/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_files.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 15:10:34 by natalia       #+#    #+#                 */
/*   Updated: 2024/08/15 16:34:48 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bnull(char **temp, int nb)
{
	while (nb >= 0)
	{
		temp[nb] = NULL;
		nb--;
	}
}
char **split_redirection_first(char *cmd)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	temp = malloc(3 * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	ft_bnull(temp, 3);
	while (cmd[i] != ' ' && cmd[i] != '\0')
		i++;
	temp[0] = ft_calloc((i + 1), sizeof(char));
	if (temp[0] == NULL)
		return (NULL);
	ft_strlcpy(temp[0], cmd, i + 1);
	i++;
	j = i;
	while (cmd[j] != '\0')
		j++;
	if (j > i)
	{
		temp[1] = ft_calloc((i + 1), sizeof(char));
		if (temp[1] == NULL)
			return (NULL);
		ft_strlcpy(temp[1], cmd + i, (j - i + 1));
	}
	return(temp);
}

int	handle_files(t_data *data, int i)
{
	bool	start_with_redirection;

	start_with_redirection = false;
	printf("i = %d\n", i);
	if (i == 0)
		start_with_redirection = true;
	if (data->cmd_table[i][0] == '>')
	{
		if (handle_outfile(data, i, start_with_redirection) != 0)
			return (1);
		i++;
	}
	else if (data->cmd_table[i][0] == '<')
	{
		if (handle_infile(data, i, start_with_redirection) != 0)
			return (error_msg("failurre on handle infile"), 1);
		i++;
	}
	return (0);
}
