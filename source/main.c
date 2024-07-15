/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:41:54 by natalia       #+#    #+#                 */
/*   Updated: 2024/07/15 17:25:26 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_input_valid(char *cmd) //testar bem essa funcao
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			if (cmd[i + 1] == '\0' || cmd[i + 1] == '|')
				return (error_msg("Syntax Error"), false);
			i++;
			if ((cmd[i] == '>' && cmd[i - 1] == '<')
				|| (cmd[i] == '<' && cmd[i - 1] == '>'))
				return (error_msg("Syntax Error"), false);
			else if (cmd[i] == '>' || cmd[i] == '<')
				i++;
			while (cmd[i] == ' ' && cmd[i] != '\0')
				i++;
			if (cmd[i] == '\0' || cmd[i] == '|' || cmd[i] == '>'
				|| cmd[i] == '<')
				return (error_msg("Syntax Error"), false);
		}
		i++;
	}
	return (true);
}

t_env	*new_env_info(char	*env)
{
	t_env	*env_list;
	char	*temp;
	int		j;

	env_list = malloc(sizeof(t_env));
	if (env_list == NULL)
		return (NULL);
	j = 0;
	while (env[j] != '=')
		j++;
	env_list->key_word = ft_calloc(sizeof(char), j + 2);
	if (env_list->key_word == NULL)
		return (NULL);
	ft_strlcpy(env_list->key_word, env, (j + 2));
	printf("key word: %s\n", env_list->key_word);
	temp = ft_strtrim_adapted(env, env_list->key_word);
	printf("temp: %s\n", temp);
	env_list->info = ft_strdup(temp);
	printf("info: %s\n", env_list->info);
	free(temp);
	env_list->next = NULL;
	return (env_list);
}

// void	env_add_back(t_env **head, void *content)
// {
// 	t_list	*current_node;
// 	t_list	*new_node;

// 	current_node = *head;
// 	while (current_node->next != NULL)
// 	{
// 		current_node = current_node->next;
// 	}
// 	new_node = ft_lstnew(content);
// 	current_node->next = new_node;
// 	new_node->prev = current_node;
// }

t_env	*parsing_env(char **env)
{
	t_env	*env_list;
	int		i;

	i = 0;
	env_list = new_env_info(env[i]);
	// while (env[i] != NULL)
	// {
	// 	env_list = add_
	// }
	return (env_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 && argv)
	{
		error_msg(" Wrong amount of args");
		error_msg("\tExecute only \033[31m./minishell\033[0m");
		return (EXIT_FAILURE);
	}
	//data.env = parsing_env(envp);
	data.path = parsing_env_path(envp);
	while (1)
	{
		data.command_line = readline("[minishell]: ");
		data.envp = envp;
		add_history(data.command_line);
		if (is_input_valid(data.command_line) == true)
		{
			parser(data);
		}
		// a funcao free pode ser colocada aqui para toda a vez que o programa volta do looping ele eh limpo?
	}
	rl_clear_history();
	return (0);
}
