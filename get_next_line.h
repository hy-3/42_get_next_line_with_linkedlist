#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
	void			*c;
	struct a_list	*next;
}	t_list;

char *get_next_line(int fd);

#endif