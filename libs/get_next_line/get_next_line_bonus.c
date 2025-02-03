/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:32:45 by mel-atti          #+#    #+#             */
/*   Updated: 2023/12/19 15:22:41 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_line_scooper(int fd, char *line_buff)
{
	char	*read_buff;
	ssize_t	rb;

	rb = 1;
	read_buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof (char));
	if (!read_buff)
		return (NULL);
	while (fd >= 0 && rb != 0 && ft_strchr2(line_buff, '\n') == NULL)
	{
		rb = read(fd, read_buff, BUFFER_SIZE);
		if (rb == -1)
		{
			free(read_buff);
			return (NULL);
		}
		read_buff[rb] = '\0';
		line_buff = ft_strjoin2(line_buff, read_buff);
	}
	free (read_buff);
	return (line_buff);
}

char	*ft_line_getter(char *line_buff)
{
	char	*cup_str;
	int		len;

	len = 0;
	if (!line_buff[len])
		return (NULL);
	while (line_buff[len] != '\0' && line_buff[len] != '\n')
		len++;
	cup_str = (char *)(malloc((len + 2) * sizeof (char)));
	if (!cup_str)
		return (NULL);
	len = 0;
	while (line_buff[len] != '\0' && line_buff[len] != '\n')
	{
		cup_str[len] = line_buff[len];
		len++;
	}
	if (line_buff[len] == '\n')
	{
		cup_str[len] = '\n';
		len++;
	}
	cup_str[len] = '\0';
	return (cup_str);
}

char	*ft_line_cleaner(char *line_buff)
{
	char	*cup_str2;
	size_t	len;
	size_t	i;

	len = 0;
	while (line_buff[len] != '\0' && line_buff[len] != '\n')
		len++;
	if (!line_buff[len])
	{
		free (line_buff);
		return (NULL);
	}
	cup_str2 = (char *)malloc(ft_strlen2(line_buff) - len);
	if (!cup_str2)
		return (NULL);
	len += 1;
	i = 0;
	while (line_buff[len] != '\0')
		cup_str2[i++] = line_buff[len++];
	cup_str2[i] = '\0';
	free (line_buff);
	return (cup_str2);
}

char	*get_next_line(int fd)
{
	static char	*line_buff[255];
	char		*rtrn_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line_buff[fd] = ft_line_scooper(fd, line_buff[fd]);
	if (!line_buff[fd])
		return (NULL);
	rtrn_line = ft_line_getter(line_buff[fd]);
	line_buff[fd] = ft_line_cleaner(line_buff[fd]);
	return (rtrn_line);
}
