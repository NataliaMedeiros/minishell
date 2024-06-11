/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/11 17:26:47 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	check_token(char *argv)
{
	if (argv[0] == '|')
		return (PIPE);
	if (argv[0] == '<')
	{
		if (argv[1] == '<')
			return (LESSLESS);
		return (LESS);
	}
	if (argv[0] == '>')
	{
		if (argv[1] == '>')
			return (GREATGREAT);
		return (GREAT);
	}
	return (WORDS);
}

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
			count += 1;
			if (cmd_line[i + 1] == '>' || cmd_line[i + 1] == '<')
				i +=2;
		}
		i++;
	}
	printf("nb cmd = %d\n", count);
	return (count);
}

char	*fill_cmd(char *cmd_line, int start, int end)
{
	char	*cmd;
	int		i;
	int		len;
	char	token;

	cmd = ft_calloc ((end - start), sizeof(char));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (cmd_line[start] == ' ')
		start++;
	len = end - start;
	token = cmd_line[end];
	printf("t = %c\n", token);
	while (i < len)
	{
		if (token != '\0' && cmd_line[start] == ' ' && cmd_line[start + 1] == token)
			break ;
		cmd[i] = cmd_line[start];
		i++;
		start++;
	}
	return (cmd);
}

char *fill_token(char *cmd_line, int i)
{
	char *token;
	int len;

	if (cmd_line[i] == '>' && cmd_line[i + 1] == '>')
		len = 2;
	else if (cmd_line[i] == '<' && cmd_line[i + 1] == '<')
		len = 2;
	else
		len =1;
	token = ft_calloc((len + 1), sizeof(char));
	//protect calloc
	token[0] = cmd_line[i];
	if (len == 2)
		token[1] = cmd_line[i + 1];
	return (token);
}

void	split_cmds(t_data **data)
{
	int		nb_cmd;
	int		nb_token;
	int		counter;
	int		i;
	int start;

	nb_cmd = nb_commands((*data)->command_line);
	(*data)->cmd = ft_calloc((nb_cmd + 1), sizeof(char));
	if ((*data)->cmd == NULL)
		return ;
		nb_token = nb_cmd - 1;
	(*data)->token = ft_calloc((nb_token + 1), sizeof(char));
	//protect null
	counter = 0;
	i = 0;
	start = 0;
	while (counter < nb_cmd)
	{
		while ((*data)->command_line[i] != '\0' && (*data)->command_line[i] != '|'
				&& (*data)->command_line[i] != '>' && (*data)->command_line[i] != '<')
			i++;
		(*data)->cmd[counter] = fill_cmd((*data)->command_line, start, i);
		if ((*data)->command_line[i] != '\0')
			(*data)->token[counter] = fill_token((*data)->command_line, i);
		printf("cmd[%d]: %s\n", counter, (*data)->cmd[counter]);
		printf("token[%d]: %s\n", counter, (*data)->token[counter]);
		counter++;
		i++;
		if ((*data)->command_line[i] != '>' || (*data)->command_line[i] != '<')
			i++;
		start = i;
	}
	(*data)->cmd[counter] = NULL;
}

t_cmd_table	*new_cmd(char *cmd, char *token)
{
	t_cmd_table	*new_command;

	new_command = ft_calloc(sizeof(t_cmd_table), 1);
	if (new_command == NULL)
		return (NULL);
	new_command->cmd = cmd;
	new_command->token = token;
	new_command->next = NULL;
	return (new_command);
}

void	add_cmd(t_cmd_table **head, t_data *data, int i)
{
	t_cmd_table	*current_command;
	t_cmd_table	*cmd;

	current_command = *head;
	while (current_command->next != NULL)
	{
		current_command = current_command->next;
	}
	cmd = new_cmd(data->cmd[i], data->token[i]);
	if (cmd == NULL)
		printf("Fail to include cmd\n");
	current_command->next = cmd;
}

t_cmd_table	*initialize_cmd_table(t_data *data)
{
	t_cmd_table	*cmd_table;
	int			i;

	split_cmds(&data);
	cmd_table = new_cmd(data->cmd[0], data->token[0]);
	i = 1;
	while (data->cmd[i] != NULL)
	{
		add_cmd(&cmd_table, data, i);
		i++;
	}
	return (cmd_table);
}

void	parser(t_data **data)
{
	t_command	*command_list;
	t_cmd_table	*cmd_table;

	command_list = initialize_commands((*data)->command_line);
	cmd_table = initialize_cmd_table(*data);
	while (command_list != NULL)
	{
		//printf("command %s and token %u\n", command_list->command, command_list->token);
		command_list = command_list->next;
	}
	while (cmd_table != NULL)
	{
		printf("command %s and token %s\n", cmd_table->cmd, cmd_table->token);
		cmd_table = cmd_table->next;
	}
}
