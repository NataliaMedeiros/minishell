#include "minishell.h"

static bool	has_cmd_before_operator(char	*cmd)
{
	int		i;

	i = 0;
	while (cmd[i] == ' ' && cmd[i] != '\0')
		i++;
	if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		return (false);
	return (true);
}

static bool	has_cmd_after_operator(char	*cmd, int i)
{
	if (cmd[i + 1] == '\0' || cmd[i + 1] == '|')
		return (false);
	if ((cmd[i] == '>' && cmd[i - 1] == '<')
		|| (cmd[i] == '<' && cmd[i - 1] == '>'))
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
	while (cmd[i] == ' ' && cmd[i] != '\0')
		i++;
	if (operator != '|' && (cmd[i] == '|' || cmd[i] == '>'
		|| cmd[i] == '<'))
		return (false);
	else if (operator == '|' && cmd[i] == '|')
		return (false);
	return (true);
}

bool	is_input_valid(char *cmd)
{
	int		i;
	char	operator;

	i = 0;
	if (has_cmd_before_operator(cmd) == false)
		return (error_msg("Syntax Error"), false);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			if (has_cmd_after_operator(cmd, i) == false)
				return (error_msg("Syntax Error"), false);
			operator = cmd[i];
			i++;
			if (has_cmd_between_operators(cmd, i, operator) == false)
				return (error_msg("Syntax Error"), false);
		}
		i++;
	}
	return (true);
}
