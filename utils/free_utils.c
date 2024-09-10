/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 13:30:17 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/10 17:37:22 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(int counter, char **cmd)
{
	if (counter == 0)
	{
		while (cmd[counter] != NULL)
		{
			if (cmd[counter] != NULL)
				free(cmd[counter]);
			counter++;
		}
	}
	else
	{
		while (counter > 0)
		{
			free(cmd[counter]);
			counter--;
		}
	}
	free(cmd);
}

void	free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->key_word);
		free(temp->info);
		free(temp);
	}
}

void	free_infile(t_infile *infile)
{
	t_infile	*temp;

	temp = infile;
	if (ft_strcmp(temp->type, "heredoc") == 0)
		unlink(temp->name);
	free(temp->name);
	free(temp);
}

void	free_parser(t_parser **parser)
{
	t_parser	*temp;

	while (*parser)
	{
		temp = *parser;
		*parser = (*parser)->pipe;
		if (temp->cmd != NULL)
			free_array(0, temp->cmd);
		if (temp->fd_outfile != -2 && temp->fd_outfile != -1)
			close(temp->fd_outfile);
		if (temp->fd_infile != -2 && temp->fd_infile != -1)
			close(temp->fd_infile);
		if (temp->outfile != NULL)
			free(temp->outfile);
		if (temp->infile != NULL)
			free_infile(temp->infile);
		free(temp);
	}
}

void	cleanup(t_data *data)
{
	if (data->cmd_line != NULL)
		free(data->cmd_line);
	if (data->cmd_table != NULL)
		free_array(0, data->cmd_table);
	if (data->parser != NULL)
		free_parser(&data->parser);
}
