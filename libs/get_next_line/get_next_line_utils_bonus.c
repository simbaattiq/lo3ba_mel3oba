/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:18:43 by mel-atti          #+#    #+#             */
/*   Updated: 2023/12/19 15:26:32 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen2(s1);
	len2 = ft_strlen2(s2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof (char));
	if (!result)
		return (NULL);
	result = ft_str_append(s1, s2, result);
	free (s1);
	return (result);
}

char	*ft_str_append(char *s1, char *s2, char *result)
{
	int	i;
	int	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strchr2(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlen2(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// READ of size 1 at 0x5030000007de thread T0
//     #0 0x55f207664596 in valid_map_chars src/parse_maputils.c:84
//     #1 0x55f207663fd2 in map_invalid src/parse_maputils.c:34
//     #2 0x55f207663e60 in parse src/parse_map.c:172
//     #3 0x55f207661128 in init src/main.c:46
//     #4 0x55f20766135c in main src/main.c:66