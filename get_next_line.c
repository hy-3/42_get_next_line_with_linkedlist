/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:37:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/23 19:32:25 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*cust_free(t_list *lst)
{
	t_list	*tmp;

	while (lst->next != NULL)
	{
		tmp = lst->next;
		free(lst->c);
		free(lst);
		lst = tmp;
	}
	if (lst->c != NULL)
		free(lst->c);
	free(lst);
	return (NULL);
}

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

char	*make_str_from_list(t_list *lst)
{
	t_list	*first;
	int		size;
	char	*res;
	int		i;

	first = lst;
	size = ft_lstsize(lst);
	res = (char *) malloc(size * sizeof(char));
	if (res == NULL)
		return (cust_free(first));
	i = 0;
	while (size-- > 0)
	{
		res[i] = (char) *(lst->c);
		lst = lst->next;
		i++;
	}
	cust_free(first);
	return (res);
}

t_list	*initilize_first_list(void)
{
	t_list	*first;

	first = (t_list *) malloc(sizeof(t_list));
	if (first == NULL)
		return (NULL);
	first->next = NULL;
	first->c = NULL;
	return (first);
}

int	read_safely(int fd, t_list *current, t_list *first)
{
	char	*buff;
	int		bytes_read;

	buff = (char *) malloc(1 * sizeof(char));
	current->c = buff;
	if (buff == NULL)
	{
		cust_free(first);
		return (-1);
	}
	bytes_read = read(fd, buff, 1);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	t_list	*first;
	t_list	*current;
	int		bytes_read;

	first = initilize_first_list();
	current = first;
	bytes_read = read_safely(fd, current, first);
	if (bytes_read == 0 || bytes_read == -1)
		return (cust_free(first));
	while (bytes_read != 0)
	{
		current->next = (t_list *) malloc(sizeof(t_list));
		if (current->next == NULL)
			return (cust_free(first));
		current = current->next;
		current->next = NULL;
		bytes_read = read_safely(fd, current, first);
		if (bytes_read == -1)
			return (NULL);
		if (*(current->c) == '\n')
			break ;
	}
	return (make_str_from_list(first));
}
//TODO: check static var
