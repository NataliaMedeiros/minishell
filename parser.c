/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/31 10:20:46 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/06 15:08:06 by natalia       ########   odam.nl         */
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
			if (cmd_line[i + 1] == '>' || cmd_line[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (count);
}

char	*fill_cmd(char *cmd_line, int start, int end)
{
	char	*cmd;
	int		i;
	int		len;

	cmd = ft_calloc ((end - start - 1), sizeof(char));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (cmd_line[start] == ' ')
		start++;
	len = end - start;
	while (i < len)
	{
		cmd[i] = cmd_line[start];
		i++;
		start++;
	}
	return (cmd);
}

char	**split_cmds(t_data *data)
{
	int		nb_cmd;
	char	**cmds;
	int		counter;
	int		i;
	int start;

	nb_cmd = nb_commands(data->command_line);
	cmds = ft_calloc((nb_cmd + 1), sizeof(char));
	if (cmds == NULL)
		return (NULL);
	counter = 0;
	i = 0;
	start = 0;
	while (counter < nb_cmd)
	{
		while (data->command_line[i] != '|' && data->command_line[i] != '\0')
			i++;
		cmds[counter] = fill_cmd(data->command_line, start, i);
		printf("count:%d-->%s<--\n", counter, cmds[counter]);
		counter++;
		i++;
		start = i;
	}
	cmds[counter] = NULL;
	printf("-->%s<--\n", cmds[0]);
	return (cmds);
}

t_cmd_table	*new_cmd(char *command)
{
	t_cmd_table	*new_command;

	new_command = malloc(sizeof(t_cmd_table));
	if (new_command == NULL)
		return (NULL);
	new_command->cmd = command;
	new_command->token = '\0';
	new_command->next = NULL;
	return (new_command);
}

void	add_cmd(t_cmd_table **head, char *content)
{
	t_cmd_table	*current_command;
	t_cmd_table	*cmd;

	current_command = *head;
	while (current_command->next != NULL)
	{
		current_command = current_command->next;
	}
	cmd = new_cmd(content);
	if (cmd == NULL)
		printf("Fail to include cmd\n");
	current_command->next = cmd;
}

t_cmd_table	*initialize_cmd_table(t_data *data)
{
	t_cmd_table	*cmd_table;
	char		**cmd;
	int			i;

	cmd = split_cmds(data);
	if (cmd == NULL)
		return (NULL);
	cmd_table = new_cmd(cmd[0]);
	i = 1;
	while (cmd[i] != NULL)
	{
		add_cmd(&cmd_table, cmd[i]);
		i++;
	}
	return (cmd_table);
}

void	parser(t_data *data)
{
	t_command	*command_list;
	t_cmd_table	*cmd_table;

	command_list = initialize_commands(data->command_line);
	cmd_table = initialize_cmd_table(data);
	while (command_list != NULL)
	{
		printf("command %s and token %u\n", command_list->command, command_list->token);
		command_list = command_list->next;
	}
	while (cmd_table != NULL)
	{
		printf("command %s and token %u\n", cmd_table->cmd, cmd_table->token);
		cmd_table = cmd_table->next;
	}
}
