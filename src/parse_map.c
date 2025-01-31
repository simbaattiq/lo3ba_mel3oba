#include <cub3D.h>

int	count_lines(int fd)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (line[i] == '1' || line[i] == '0')
			j++;
		free(line);
		line = get_next_line(fd);
	}
	return (j);
}

char	*get_parameters(int fd, t_data *data)
{
	int		i;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (line[i] && (line[i] == '0' || line[i] == '1'))
			return (line);
		// else if (line[i] && line[i] == 'N')
		// 	data->no = ft_strdup(&line[i + 3]);
		// else if (line[i] && line[i] == 'S')
		// 	data->so = ft_strdup(&line[i + 3]);
		// else if (line[i] && line[i] == 'W')
		// 	data->we = ft_strdup(&line[i + 3]);
		// else if (line[i] && line[i] == 'E')
		// 	data->ea = ft_strdup(&line[i + 3]);

		else if (line[i] && line[i] == 'N' && line[i + 1] == 'O')
			data->no = ft_strdup(&line[i + 3]);
		else if (line[i] && line[i] == 'S' && line[i + 1] == 'O')
			data->so = ft_strdup(&line[i + 3]);
		else if (line[i] && line[i] == 'W' && line[i + 1] == 'E')
			data->we = ft_strdup(&line[i + 3]);
		else if (line[i] && line[i] == 'E' && line[i + 1] == 'A')
			data->ea = ft_strdup(&line[i + 3]);
		else if (line[i] && line[i] == 'F')
			data->f = ft_strdup(&line[i + 2]);
		else if (line[i] && line[i] == 'C')
			data->c = ft_strdup(&line[i + 2]);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

int	check_player_position(t_data *data, int i, int j, int *p)
{
	// if (data->map[i][j] == 'N')
	if (data->map[i][j] == 'N' && data->map[i][j + 1] != 'O') //// // /
		data->player->angle = 3 * M_PI / 2;
	else if (data->map[i][j] == 'S' && data->map[i][j + 1] != 'O')
		data->player->angle = M_PI / 2;
	else if (data->map[i][j] == 'E' && data->map[i][j + 1] != 'A')
		data->player->angle = 0;
	else if (data->map[i][j] == 'W' && data->map[i][j + 1] != 'E')
		data->player->angle = M_PI;
	data->map[i][j] = '0';
	data->player->x = j + 0.5; ///
	data->player->y = i + 0.5; ///
	(*p)++; // will always increment even if there is no player!!?
	return (0);
}

// parse player:
// traverse to the start of the map
// checks if there is a palyer on the map
int	ft_ft(int fd, t_data *data)
{
	int		i;
	char	*line;
	int		j;
	int		p;

	line = get_parameters(fd, data);
	p = 0;
	i = 0;

	while (line)
	{
		data->map[i] = line;
		j = -1;
		data->map_w = 0;
		while (data->map[i][++j])
		{
			if (data->map[i][j] != '\n')
				data->map_w++;
			else
				data->map[i][j] = '\0';
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				check_player_position(data, i, j, &p);
		}
		i++;
		line = get_next_line(fd);
	}
	if (p != 1)
		return (1);


	data->map[i] = NULL; //// // /


	return (0);
}


/*set data*/
int	set_map(char *file, t_data *data)
{
	int	fd1;
	int	fd2;

	fd1 = open(file, O_RDONLY);
	fd2 = open(file, O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		printf("Error\ncan't open the map's file.\n");
		return (1);
	}
	data->map_h = count_lines(fd1);
	data->map = (char **)malloc(sizeof(char *) * (data->map_h + 1));
	if (ft_ft(fd2, data)) //
		return (1);
	data->map[data->map_h] = NULL;
	close(fd1);
	close(fd2);
	return (0);
}

/*file checks*/
int	check_file(char *file)
{
	int	len;
	int	j;

	len = ft_strlen(file);
	j = ft_strlen(".cub");
	if (len <= j || ft_strncmp(&file[len - j], ".cub", j) || ft_strchr(file,
			'/') == &file[ft_strlen(file) - 5])
	{
		printf("Error\nthe map file should be *.cub\n");
		return (1);
	}
	return (0);
}


/*lparsing*/
int	parse(char *file, t_data *data)
{
	data->map = NULL;
	if (check_file(file))
		return (1);

	if (map_invalid(file))
		return (1);
	if (set_map(file, data)) //
		return (1);

	if (check_configs(data)) //
		return (1);

	return (0);
}

////////////////////////
int check_configs(t_data *data)
{
	if (check_fnc(data))
		return (1);
	if (check_texture(data))
		return (1);

	//success
	return (0);
}

// F 220,100,0
// C 225,30,0

int check_fnc(t_data *data)
{
	if (invalid_fcchar(data->c))
	{
		printf("Error\n invalid char in ceiling configs\n");
		return (1);
	}
	if (invalid_fcchar(data->f))
	{
		printf("Error\n invalid char in floor configs\n");
		return (1);
	}
	if (check_rgb_num(data))
	{
		return(1);
	}
	return (0); // success!!
}

int invalid_fcchar(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	while(str[i])
	{
		if (invalid_char(str[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

bool invalid_char(char c)
{
	// ;
	if (c != ',' && !iswhite_space(c) && !ft_isdigit_two(c))
		return (true);
	else
		return (false);
}

bool iswhite_space(char c)
{
	if (c != 32 && c != '\t' && c !='\v')
		return (0);
	else
		return (1);
}

bool ft_isdigit_two(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

///////////////////////////////////
int check_texture(t_data *data)
{
	int fd[4];
	int i;

	fd[0] = open(data->no, O_RDONLY);
	fd[1] = open(data->so, O_RDONLY);
	fd[2] = open(data->we, O_RDONLY);
	fd[3] = open(data->ea, O_RDONLY);
	i = -1;
	while (++i < 4)
	{
		if (fd[i] < 0)
		{
			printf("Error\n can't open files\n");
			i = -1;
			while(++i < 4)
				close(fd[i]);
			return (1);
		}
	}
	i = -1;
	while(++i < 4)
		close(fd[i]);
	return (0);

}

////////////////////////////

int	check_rgb_num(t_data *data)
{
	char **tmp_fvalue;
	char **tmp_cvalue;

	tmp_fvalue = ft_split(data->f, ',');
	tmp_cvalue = ft_split(data->c, ',');

	if (!tmp_cvalue || !tmp_fvalue)
	{
		printf("Error\nMalloc!!!\n");
		return (1); //error
	}
	if (ft_check_bound(tmp_fvalue))
	{
		printf("Error\nFloor RGB values out of range 0-255\n");
		double_free(tmp_fvalue);
		double_free(tmp_cvalue);
		return (1);
	}
	if (ft_check_bound(tmp_cvalue))
	{
		printf("Error\nCeiling RGB values out of range 0-255\n");
		double_free(tmp_fvalue);
		double_free(tmp_cvalue);
		return (1);
	}
	double_free(tmp_fvalue);
	double_free(tmp_cvalue);
	return (0);
}

int ft_check_bound(char **ptr)
{
	int num;
	int i;

	i = 0;
	while(ptr[i])
	{
		num = ft_atoi(ptr[i]);
		if (num < 0 || num > 255)
		{
			return (1);
		}
		i++;
	}
	return (0);
}