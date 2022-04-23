/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:37:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/23 16:37:37 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*current_position;

	if (lst == NULL)
		return (0);
	count = 1;
	current_position = lst->next;
	while (current_position != NULL)
	{
		count++;
		current_position = current_position->next;
	}
	return (count);
}

char	*copy_str_from_list(t_list *lst)
{
	int		size;
	char	*res;
	int		i;

	size = ft_lstsize(lst);
	res = (char *) malloc(size * sizeof(char));
	if (res == NULL)
		return (NULL); //TODO: when res == NULL
	i = 0;
	while (size-- > 0)
	{
		res[i] = (char) *(lst->c);
		lst = lst->next;
		i++;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	t_list	*lst;
	t_list	*first_lst;
	int		bytes_read;
	char	*buff;

	lst = (t_list *) malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	first_lst = lst;
	buff = (char *) malloc(1 * sizeof(char));
	if (buff == NULL)
		return (NULL);
	bytes_read = read(fd, buff, 1);
	lst->c = buff;
	if (bytes_read != 0)
	{
		while (bytes_read != 0)
		{
			lst->next = (t_list *) malloc(sizeof(t_list));
			if (lst->next == NULL)
				return (NULL); //TODO: call free functions to free everything.
			lst = lst->next;
			lst->next = NULL;
			buff = (char *) malloc(1 * sizeof(char));
			if (buff == NULL)
				return (NULL);
			bytes_read = read(fd, buff, 1);
			lst->c = buff;
			if (*(lst->c) == '\n')
				break ;
		}
	}
	else
	{
		free(lst);
		return (NULL);
	}
	return (copy_str_from_list(first_lst));
}

//TODO: check static var
//TODO: test fd other than stdin

#include <stdio.h>
int	main(void)
{
	char *r = get_next_line(1);
	printf(">>%s<<\n", r);
	return (0);
}

