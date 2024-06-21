/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/21 20:10:40 by natalia       ########   odam.nl         */
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

void	free_array(int	counter, char **cmd)
{
	while (counter > 0)
	{
		free(cmd[counter]);
		counter--;
	}
	free(cmd);
}

char	**split_cmds(t_data data)
{
	int		nb_args;
	int		counter;
	int		i;
	int		start;
	char	**cmd;

	nb_args = nb_commands(data.command_line);
	cmd = ft_calloc((nb_args + 1), sizeof(char *));
	if (cmd == NULL)
		return (NULL);
	counter = 0;
	i = 0;
	while (counter < nb_args)
	{
		start = i;
		while (data.command_line[i] != '\0' && data.command_line[i] != '|'
				&& data.command_line[i] != '>' && data.command_line[i] != '<')
			i++;
		cmd[counter] = ft_substr(data.command_line, start, (i - start));
		if (cmd[counter] == NULL)
			return (free_array(counter, cmd), NULL);
		counter++;
		start = i;
		if (counter == nb_args)
			break;
		if (data.command_line[i] == '>' || data.command_line[i] == '<')
			i++;
		cmd[counter] = ft_substr(data.command_line, start, (i + 1 - start));
		if (cmd[counter] == NULL)
			return (free_array(counter, cmd), NULL);
		counter++;
		i++;
	}
	cmd[counter] = NULL;
	return (cmd);
}

// t_cmd_table	*new_cmd(char *cmd, char *token)
// {
// 	t_cmd_table	*new_command;

// 	new_command = ft_calloc(sizeof(t_cmd_table), 1);
// 	if (new_command == NULL)
// 		return (NULL);
// 	new_command->cmd = cmd;
// 	new_command->token = token;
// 	new_command->next = NULL;
// 	return (new_command);
// }

// void	add_cmd(t_cmd_table **head, t_data *data, int i)
// {
// 	t_cmd_table	*current_command;
// 	t_cmd_table	*cmd;

// 	current_command = *head;
// 	while (current_command->next != NULL)
// 	{
// 		current_command = current_command->next;
// 	}
// 	cmd = new_cmd(data->cmd[i], data->token[i]);
// 	if (cmd == NULL)
// 		printf("Fail to include cmd\n");
// 	current_command->next = cmd;
// }

// t_cmd_table	*initialize_cmd_table(t_data *data)
// {
// 	t_cmd_table	*cmd_table;
// 	int			i;

// 	split_cmds(data);
// 	printf("		cmd[0]: %s\n", (data)->cmd[0]);
// 	printf("		token[0]: %s\n", (data)->token[0]);
// 	cmd_table = new_cmd(data->cmd[0], data->token[0]);
// 	i = 1;
// 	while (data->cmd[i] != NULL)
// 	{
// 		add_cmd(&cmd_table, data, i);
// 		i++;
// 	}
// 	return (cmd_table);
// }

void	print_array(char **array)
{
	int i;

	i = 0;
	while(array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	parser(t_data data)
{
	int i;
	t_mini	*mini_data;

	data.cmd = split_cmds(data);
	i = 0;
	mini_data = malloc(sizeof(t_mini));
	if (mini_data == NULL)
		return ; //acho que tenho que fazer free do data.cmd
	//mini_data->ft_infile = NULL;
	//mini_data->ft_outfile = NULL;
	mini_data->infile = NULL;
	mini_data->outfile = NULL;
	while (data.cmd[i] != NULL)
	{
		printf("[data]: %s\n", data.cmd[i]);
		if (data.cmd[i][0] == '>')
		{
			i++;
			mini_data->outfile = ft_strdup(data.cmd[i]);
			if (data.cmd[i][1] == '>')
				mini_data->fd_outfile = open(mini_data->outfile, O_CREAT |  O_APPEND);
			else
				mini_data->fd_outfile = open(mini_data->outfile, O_CREAT |  O_WRONLY);
			printf("outfile: %s and fd: %d\n", mini_data->outfile, mini_data->fd_outfile);
		}
		else if(data.cmd[i][0] == '<')
		{
			i++;
			mini_data->infile = ft_strdup(data.cmd[i]);
			//if (data.cmd[i][1] == '>')
				//I don't know what to put here
			//else
				mini_data->fd_infile = open(mini_data->infile, O_RDONLY);
			printf("infile: %s and fd: %d\n", mini_data->infile, mini_data->fd_infile);
		}
		else
		{
			mini_data->cmd = ft_split(data.cmd[i], ' ');
			print_array(mini_data->cmd);
		}
		i++;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_element;

	new_element = malloc(sizeof(t_list));
	if (new_element == NULL)
		return (NULL);
	new_element->content = content;
	new_element->next = NULL;
	return (new_element);
}
