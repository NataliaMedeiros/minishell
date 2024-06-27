#include "../minishell.h"

/*This functions remove quotes (simple or double) of the heredoc limiter*/
static char	*remove_lim_quotes(char *limiter)
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

/*This functions remove backslash of the heredoc limiter
- Check if we should handle this, because I checked on bash and it removes the backslash*/
static char	*remove_lim_backslash(char *limiter)
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
		if (limiter[i] != '\\')
		{
			new_limiter[j] = limiter[i];
			j++;
		}
		i++;
	}
	return (new_limiter);
}

char	*var_replace(char *line, char *var_exp, int start, int end)
{
	char	*sub;
	char	*sub2;
	char	*join;
	char	*newline;

	sub = ft_substr(line, 0, start - 1);
	join = ft_strjoin(sub, var_exp);
	sub2 = ft_substr(line, end, ft_strlen(line));
	newline = ft_strjoin(join, sub2);
	free(sub);
	free(join);
	free(sub2);
	return (newline);
}

void	get_var(char *line, int i, t_data data)
{
	int	start;
	int	len;
	char *var;
	int	j;
	char	*var_value;
	// char *new_line;

	start = i;
	while (line[i] != ' ' && line[i] != '"' && line[i] != '\0')
		i++;
	len = i - start;
	var = ft_substr(line, start, len);
	printf("var = %s\n", var);
	j = 0;
	while (data.envp[j])
	{
		if (ft_strncmp(data.envp[j], var, len) == 0)
		{
			var_value = ft_strdup(data.envp[j] + (len + 1));
			printf("%s\n", var_value);
			break;
		}
		j++;
	}
	// new_line = var_replace(line, var_value, start, i);
	// printf("new_line = %s\n", new_line);
}

void	handle_dollar_sign(char *line, t_data data)
{
	int		i;

	if (ft_strchr(line, '"') != NULL || ft_strchr(line, '\'') == NULL)
	{
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == '$')
				get_var(line, i + 1, data);
			i++;
		}
	}
}

/* This functions create the space op terminal to receive the heredoc input, reads this imput,
checks delimiter (remover quotes and backslash if necessary) and closing the typing space on
terminal when limiter is placed as input */
/* PS: bash behavio: if the limiter is typed followed by more text it not works as limiter,
if limiter is typed between quotes (simple os double), the quotes should be removed and
the same happens with backslash*/
/* PS2: In this function I copied the limiter from the parser->imput checar se compensa
deixar assim ou usar o strdup(cmd_lst[i+1])*/
int	handle_heredoc(t_parser **parser, t_data data)
{
	char	*line;
	char	*limiter;

	(*parser)->fd_infile = open((*parser)->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((*parser)->fd_infile == -1)
		return (printf("Fail to open infile\n"), 1);
	if (ft_strchr((*parser)->infile, '"') != NULL || ft_strchr((*parser)->infile, '\'') != NULL)
		limiter = remove_lim_quotes((*parser)->infile);
	else if (ft_strchr((*parser)->infile, '\\') != NULL)
		limiter = remove_lim_backslash((*parser)->infile);
	else
		limiter = (*parser)->infile;
	line = readline(">");
	while (line != NULL)
	{
		if (ft_strlen(line) == ft_strlen(limiter) &&
			ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break;
		//implementar dollar sign
		if (ft_strchr(line, '$') != NULL)
		{
			handle_dollar_sign(line, data);
			printf("Handle dollar sign\n");
		}
		write((*parser)->fd_infile, line, strlen(line));
		write((*parser)->fd_infile, "\n", 1);
		free(line); //checkar if it is needed
		line = readline(">");
	}
	return (0);
}

