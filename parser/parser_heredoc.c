/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: natalia <natalia@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:20:29 by nmedeiro      #+#    #+#                 */
/*   Updated: 2024/08/02 12:52:53 by natalia       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
- Check if we should handle this, because I checked on
bash and it removes the backslash*/
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

char	*find_limiter(t_parser **parser)
{
	char	*limiter;

	if (ft_strchr((*parser)->infile->name, '"') != NULL
		|| ft_strchr((*parser)->infile->name, '\'') != NULL)
		limiter = remove_lim_quotes((*parser)->infile->name);
	else if (ft_strchr((*parser)->infile->name, '\\') != NULL)
		limiter = remove_lim_backslash((*parser)->infile->name);
	else
		limiter = (*parser)->infile->name;
	return (limiter);
}

/* This functions create the space op terminal to receive the heredoc
input, reads this imput,checks delimiter (remover quotes and backslash
if necessary) and closing the typing space on terminal when limiter is
placed as input */
/* PS: bash behavio: if the limiter is typed followed by more text it
not works as limiter,if limiter is typed between quotes (simple os
double), the quotes should be removed and the same happens with backslash*/
/* PS2: In this function I copied the limiter from the parser->imput
checar se compensa deixar assim ou usar o strdup(cmd_lst[i+1])*/
int	handle_heredoc(t_parser **parser, t_data data)
{
	char	*line;
	char	*limiter;

	//printf("Entrei no handle heredoc\n");
	// printf("name: %s\n", (*parser)->infile->name);
	(*parser)->fd_infile = open((*parser)->infile->name,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((*parser)->fd_infile == -1)
	{
		perror("Erro ao abrir/criar o arquivo");
        fprintf(stderr, "Erro: %s\n", strerror(errno));
		return (printf("Fail to open infile\n"), 1);
	}
	limiter = find_limiter(parser);
	line = readline(">");
	while (line != NULL)
	{
		if (ft_strlen(line) == ft_strlen(limiter)
			&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		while (ft_strchr(line, '$') != NULL)
			line = handle_dollar_sign(line, data);
		write((*parser)->fd_infile, line, strlen(line));
		write((*parser)->fd_infile, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
	return (0);
}
