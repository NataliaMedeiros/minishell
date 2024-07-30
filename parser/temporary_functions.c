#include "../minishell.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("->%s<-\n", array[i]);
		i++;
	}
}

void	print_struct(t_parser *head)
{
	int	i;

	i = 1;
	while (head != NULL)
	{
		printf("flag %d\n", head->flag);
		printf("fd in%d\n", head->fd_infile);
		printf("fd out%d\n", head->fd_outfile);
		// printf("PIPE exist: %d\n", head->nb_pipes);
		printf("\033[31mstruct[%d]:\n\033[0m", i);
		if (head->cmd != NULL)
			print_array(head->cmd);
		printf("\033[31moutfile: \033[0m->%s<-\n", head->outfile ? head->outfile : "None");
		printf("\033[31mofd_utfile: \033[0m->%d<-\n", head->fd_outfile);
		while (head->infile != NULL)
		{
			printf("\033[31minfile: \033[0m->%s<-\n", head->infile->name ? head->infile->name : "None" );
			printf("\033[31minfile: \033[0m->%d<-\n", head->fd_infile);
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
