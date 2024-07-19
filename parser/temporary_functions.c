#include "../minishell.h"

void	print_array(char **array)
{
	int i;

	i = 0;
	while(array[i] != NULL)
	{
		printf("->%s<-\n", array[i]);
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
		printf("\033[31mstruct[%d]:\n\033[0m", i);
		if (head->cmd != NULL)
			print_array(head->cmd);
		printf("\033[31moutfile: \033[0m->%s<-\n", head->outfile ? head->outfile : "None");
		while (head->infile != NULL)
		{
			printf("\033[31minfile: \033[0m->%s<-\n", head->infile->name ? head->infile->name : "None" );
			head->infile = head->infile->next;
		}
		head = head->pipe;
		i++;
	}
}

void	print_env(t_env *env)
{
	while (env->next != NULL)
	{
		printf("key word: %s\nInfo:%s\n", env->key_word, env->info);
		env = env->next;
	}
}
