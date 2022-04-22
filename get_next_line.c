#include "get_next_line.h"

char	*get_next_line(int fd)
{
	t_list *res;

	res = (t_list *) malloc(sizeof(t_list));
	if (res == NULL)
		return (NULL);
	if (read(fd, res->c, 1) != 0)
		if (res->c != '\n')
			get_next_line(fd);
	// look ft_lstmap
	// get size of list
	// malloc char* with above size
	// copy evrything to malloced char* and return it.
	// set static var for next line.
}
