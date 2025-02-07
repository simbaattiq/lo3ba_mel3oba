/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 04:18:18 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 04:18:49 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_extension(t_data *data)
{
	if (invalide_extension(data->no) || invalide_extension(data->so)
		|| invalide_extension(data->we) || invalide_extension(data->ea))
	{
		return (1);
	}
	return (0);
}

int	invalide_extension(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (str[len] != '.' && len > 0)
		len--;
	if (ft_strncmp(&str[len], ".xpm", 5))
	{
		return (1);
	}
	return (0);
}
