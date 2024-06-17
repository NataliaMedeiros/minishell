/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_command_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/06 14:44:28 by natalia       #+#    #+#                 */
/*   Updated: 2024/06/17 11:49:11 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(char *command)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (NULL);
	new_command->command = command;
	new_command->token = check_token(command);
	new_command->next = NULL;
	return (new_command);
}

void	add_command_back(t_command **head, char *content)
{
	t_command	*current_command;
	t_command	*command;

	current_command = *head;
	while (current_command->next != NULL)
	{
		current_command = current_command->next;
	}
	command = new_command(content);
	if (command == NULL)
		printf("Fail to include philo\n");
	current_command->next = command;
	//incluir link pra head
}

int	has_quotes(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*remove_spaces(char *argv)
{
	char	*new_argv;
	int		i;
	int		j;
	int quotes =0;

	new_argv = ft_calloc((ft_strlen(argv) + 1), sizeof(char));
	i = 0;
	j = 0;
	while (argv[i] == ' ' || argv[i] == '\t')
		i++;
	while (argv[i] != '\0')
	{
		if (argv[i] == '"')
			quotes++;
		if ((argv[i] == ' ' || argv[i] == '\t' || argv[i] == '\n')
			&& quotes % 2 == 0)
			new_argv[j] = '"';
		else
			new_argv[j] = argv[i];
		j++;
		i++;
	}
	return (new_argv);
}



t_command	*last_node(t_command *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
