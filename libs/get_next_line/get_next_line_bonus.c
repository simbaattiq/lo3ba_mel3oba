/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:04:15 by zelkalai          #+#    #+#             */
/*   Updated: 2024/02/16 02:34:15 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clist(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = *list;
	while (last_node->next)
	{
		last_node = last_node->next;
	}
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i])
		buf[k++] = last_node->content[++i];
	buf[k] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_the_line(t_list *list)
{
	int		l;
	char	*the_line;

	if (list == NULL)
		return (NULL);
	l = llist(list);
	the_line = malloc(l + 1);
	if (the_line == NULL)
		return (NULL);
	copy_the_list(list, the_line);
	return (the_line);
}

void	add_to_list(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->content = buf;
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		last_node = *list;
		while (last_node->next != NULL)
		{
			last_node = last_node->next;
		}
		last_node->next = new_node;
	}
}

void	list_maker(t_list **list, int fd)
{
	ssize_t		r;
	char		*buf;

	while (!newline_checker(*list))
	{
		buf = malloc((size_t)BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
		{
			free(buf);
			return ;
		}
		buf[r] = '\0';
		add_to_list(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*the_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	list_maker(&list[fd], fd);
	if (list[fd] == NULL)
		return (NULL);
	the_line = get_the_line(list[fd]);
	clist(&list[fd]);
	return (the_line);
}
