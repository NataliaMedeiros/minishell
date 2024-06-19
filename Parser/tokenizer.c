#include "../minishell.h"

t_token	check_token(char *argv)
{
	if (argv[0] == '|')
		return (PIPE);
	if (argv[0] == '<')
	{
		if (argv[1] == '<')
			return (HEREDOC);
		return (IN);
	}
	if (argv[0] == '>')
	{
		if (argv[1] == '>')
			return (APPEND);
		return (OUT);
	}
	return (WORDS);
}
