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

void	print_struct(t_parser	*head)
{
	int	i;

	i = 1;
	printf("printing mini:\n");
	while (head != NULL)
	{
		printf("struct[%d]:\n", i);
		if (head->cmd != NULL)
			print_array(head->cmd);
		printf("outfile: %s\n", head->outfile ? head->outfile : "None");
		printf("infile: %s\n", head->infile ? head->infile : "None");
		head = head->pipe;
		i++;
	}
}
