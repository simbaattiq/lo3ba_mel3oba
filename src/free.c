/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:25:38 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:25:39 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map && data->map[i])
	{
		// printf("i: [%d]", i);

		if (data->map[i])
			free(data->map[i]);
		i++;
	}

	////////////////////////// without this == leaks if rgb >/< range
	if (data->f)
		free(data->f);
	if (data->c)
		free(data->c);
	if (data->no)
		free(data->no);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->so)
		free(data->so);

	//////////////////////////


	if (data->map)
		free(data->map);
}

void	clean_all(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free_map(mlx->data);
	free(mlx->mlx);
}


void double_free(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}

int free_error_fd(char *msg, char **map, int fd, int fd2)
{
    if (msg)
    {
    	printf("%s", msg);
    }
    if (map)
        double_free(map);
    close(fd);
    close(fd2);
	return (1);
}

int error_tf(char *msg, char **cvalue, char **fvalue)
{
	if (msg)
	{
		printf("%s", msg);
	}
	if (cvalue)
	{
		double_free(cvalue);
	}
	if (fvalue)
	{
		double_free(fvalue);
	}
	return (1);

}

int	error_msg(char *msg, int status)
{
	if (msg)
		printf("%s", msg);
	return (status);
}