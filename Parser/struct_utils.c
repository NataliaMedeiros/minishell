#include "../minishell.h"

t_parser	*new_struct()
{
	t_parser	*new_element;

	new_element = malloc(sizeof(t_parser));
	if (new_element == NULL)
		return (NULL);
	new_element->infile = NULL;
	new_element->outfile = NULL;
	new_element->pipe = NULL;
	return (new_element);
}
