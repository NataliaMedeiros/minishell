#include "../minishell.h"

void	print_array(char **array)
{
	int i;

	i = 0;
	while(array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	print_struct(t_parser *head)
{
	int	i;

	i = 1;
	// printf("printing mini:\n");
	while (head != NULL)
	{
		printf("\033[31mstruct[%d]:\n \033[0m", i);
		if (head->cmd != NULL)
			print_array(head->cmd);
		printf("\033[31moutfile: %s\n \033[0m", head->outfile ? head->outfile : "None");
		printf("\033[31minfile: %s\n \033[0m", head->infile ? head->infile : "None" );
		head = head->pipe;
		i++;
	}
}
