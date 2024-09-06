/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 13:30:17 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/09/06 15:29:16 by nmedeiro      ########   odam.nl         */
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
	// *env = NULL;
}

void	free_infile(t_infile *infile)
{
	t_infile	*temp;

	while (infile)
	{
		temp = infile;
		infile = infile->next;
		if (ft_strcmp(temp->type, "heredoc") == 0)
			unlink(temp->name);
		free(temp);
	}
	// *env = NULL;
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
		free(temp->outfile);
		free_infile(temp->infile);
		free(temp);
	}
	// *env = NULL;
}

void	cleanup(t_data *data)
{
	// if (data.envp != NULL)
	// 	free(data.envp);
	// if (data.env != NULL)
	// {
	// 	printf("clean 1!\n");
	// 	free_env(&data.env);
	// }
	if (data->cmd_line != NULL)
	{
		// printf("CLEAN 2\n");ma
		free(data->cmd_line);
	}
	if (data->cmd_table != NULL)
	{
		// printf("CLEAN 3\n");
		free_array(0, data->cmd_table);
	}
	if (data->parser != NULL)
	{
		// printf("CLEAN 4\n");
		free_parser(&data->parser);
	}
}
