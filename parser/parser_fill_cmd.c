#include "../minishell.h"

static char	*remove_quotes(char *limiter)
{
	char	*new_limiter;
	int		i;
	int		j;

	new_limiter = ft_calloc(sizeof(char), ft_strlen(limiter) - 1);
	if (new_limiter == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (limiter[i] != '\0')
	{
		if (limiter[i] != '"' && limiter[i] != '\'')
		{
			new_limiter[j] = limiter[i];
			j++;
		}
		i++;
	}
	return (new_limiter);
}

static bool	has_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '"' || arg[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

static int	fill_cmd_mode_echo(t_parser	**parser, char *cmd)
{
	char	*temp;

	(*parser)->cmd = ft_calloc(sizeof(char *), 3);
	if ((*parser)->cmd == NULL)
		return (1);
	(*parser)->cmd[0] = ft_strdup("echo");
	if ((*parser)->cmd[0] == NULL)
		return (1);
	temp = ft_strtrim(cmd, "echo "); // o espaco esta fazendo a primeira letra da palavra sumir mas sem ele, fica um espaco quando eh copiado
	if (temp == NULL)
		return (1);
	if (has_quotes(temp) == true)
		(*parser)->cmd[1] = remove_quotes(temp);
	else
		(*parser)->cmd[1] = ft_strdup(temp);
	if ((*parser)->cmd[1] == NULL)
		return (1);
	free(temp);
	return (0);
}

int	fill_cmd(t_parser **parser, char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
	{
		if (fill_cmd_mode_echo(parser, cmd) == 1)
			return(error_msg("Failure to fill cmd\n"), 1);
	}
	else
		(*parser)->cmd = ft_split(cmd, ' ');
	if ((*parser)->cmd == NULL)
		return(error_msg("Failure to fill cmd\n"), 1);
	return (0);
}
