/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 13:49:47 by edribeir      #+#    #+#                 */
/*   Updated: 2024/06/18 14:51:56 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//not working need to think more about


// int	memory_counter(char *prompt, int delimiter, char simbol)
// {
// 	int	counter;

// 	counter = 0;
// 	while(prompt[counter] != simbol)
// 	{
// 		counter++;
// 	}
// }

// t_data ft_parsing(char *prompt)
// {
// 	t_data	data;
// 	int		i;
// 	int		counter;

// 	i = 0;
// 	counter = 0;
// 	while (prompt[i] != '\0')
// 	{
// 		if (prompt[i] == '>')
// 		{
// 			counter = i;
// 			malloc(counter * sizeof(char));
// 		}
// 		if (prompt[i] == '|')
// 		{
// 			while (prompt[i] != '\0')
// 			{
// 				data.pipe.child2 = prompt[i];
// 				i++;
// 			}
// 			return (data);
// 		}
// 		i++;
// 	}
// 	return (data);
// }