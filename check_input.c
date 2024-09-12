/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 13:52:56 by edribeir      #+#    #+#                 */
/*   Updated: 2024/09/12 10:37:41 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_cmd_before_operator(char	*cmd)
{
	int		i;

	i = 0;
	while (cmd[i] == ' ' && cmd[i] != '\0')
		i++;
	if (cmd[i] == '|')
		return (false);
	return (true);
}

static bool	has_cmd_after_operator(char	*cmd, int i)
{
	if (cmd[i + 1] == '\0' || cmd[i + 1] == '|')
		return (false);
	if ((cmd[i + 1] == '>' || cmd[i + 1] == '<') && cmd[i + 2] == '\0')
		return (false);
	if (i != 0 && ((cmd[i] == '>' && cmd[i - 1] == '<')
			|| (cmd[i] == '<' && cmd[i - 1] == '>')))
		return (false);
	i++;
	while (cmd[i] == ' ' && cmd[i] != '\0')
		i++;
	if (cmd[i] == '\0')
		return (false);
	return (true);
}

static bool	has_cmd_between_operators(char	*cmd, int i, char operator)
{
	if ((operator == '>' && cmd[i] == '>')
		|| (operator == '<' && cmd[i] == '<'))
		i++;
	while (cmd[i] == ' ' && cmd[i] != '\0')
		i++;
	if (operator != '|' && (cmd[i] == '|' || cmd[i] == '>'
			|| cmd[i] == '<'))
		return (false);
	else if (operator == '|' && cmd[i] == '|')
		return (false);
	return (true);
}

bool	has_unclosed_quote(char *cmd)
{
	int		i;
	bool	has_double_quotes;
	bool	has_single_quotes;

	i = 0;
	has_double_quotes = false;
	has_single_quotes = false;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"' && !has_single_quotes)
			has_double_quotes = !has_double_quotes;
		if (cmd[i] == '\'' && !has_double_quotes)
			has_single_quotes = !has_single_quotes;
		i++;
	}
	if (has_double_quotes == true || has_single_quotes == true)
		return (true);
	return (false);
}

bool	is_input_valid(char *cmd)
{
	int		i;
	char	operator;

	i = 0;
	if (has_no_arg(cmd) == false)
		return (error_msg("Syntax Error"), free(cmd), false);
	if (has_cmd_before_operator(cmd) == false)
		return (error_msg("Syntax Error"), free(cmd), false);
	if (has_unclosed_quote(cmd) == true)
		return (error_msg("Syntax error: unclosed quotes"), free(cmd), false);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			if (has_cmd_after_operator(cmd, i) == false)
				return (error_msg("Syntax Error"), free(cmd), false);
			operator = cmd[i];
			i++;
			if (has_cmd_between_operators(cmd, i, operator) == false)
				return (error_msg("Syntax Error"), free(cmd), false);
		}
		i++;
	}
	return (true);
}
