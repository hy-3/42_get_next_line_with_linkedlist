/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:37:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/23 18:06:10 by hiyamamo         ###   ########.fr       */
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

t_list	*initilize_list_with_first_char(fd)
{
	t_list	*first_lst;

	first_lst = (t_list *) malloc(sizeof(t_list));
	if (first_lst == NULL)
		return (NULL);
	return (first_lst);
}

int	read_char(int fd, t_list *lst)
{
	char	*buff;
	int		bytes_read;

	buff = (char *) malloc(1 * sizeof(char));
	if (buff == NULL)
	{
		free(lst);
		return (0);
	}
	bytes_read = read(fd, buff, 1);
	lst->c = buff;
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	t_list	*lst;
	t_list	*first_lst;
	t_list	*tmp;
	int		bytes_read;
	char	*buff;

	first_lst = initilize_list_with_first_char(fd);
	lst = first_lst;
	bytes_read = read_char(fd, lst);
	if (bytes_read == 0)
		return (NULL);
	while (bytes_read != 0)
	{
		lst->next = (t_list *) malloc(sizeof(t_list));
		if (lst->next == NULL)
		{
			lst = first_lst;
			while (lst->next != NULL)
			{
				tmp = lst->next;
				free(lst->c);
				free(lst);
				lst = tmp;
			}
			return (NULL);
		}
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
	return (copy_str_from_list(first_lst));
}

//TODO: free buff(= free lst->c)
//TODO: check static var
