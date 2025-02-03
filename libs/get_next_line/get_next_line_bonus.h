/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:14:41 by mel-atti          #+#    #+#             */
/*   Updated: 2023/12/19 15:24:03 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_line_scooper(int fd, char *line_buff);

char	*ft_line_getter(char *line_buff);

char	*ft_line_cleaner(char *line_buff);

char	*get_next_line(int fd);

char	*ft_strjoin2(char *s1, char *s2);

char	*ft_str_append(char *s1, char *s2, char *result);

char	*ft_strchr2(char *str, int c);
// char    *ft_strchr(const char *s, int c);

size_t	ft_strlen2(char *str);

#endif
