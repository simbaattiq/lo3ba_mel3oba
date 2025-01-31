

#include <cub3D.h>

///////////////////////////////////////////////


// int		map_invalid(char *file, t_data *data)
int		map_invalid(char *file)
{
	char **map;

    int fd = open(file, O_RDONLY);
    int fd2 = open(file, O_RDONLY);

    int lcount = count_lines(fd2);
  
    if (fd < 0 || fd2 < 0)
    {
        return(1);
    }
	// data->map = strdup_map(fd, lcount);
	map = strdup_map(fd, lcount);

	if (!map)
	{
		printf("Error: strdup_douplep()\n");
        close(fd);
        close(fd2);
		return (1); // error
	}
	if (!map_closed(map, lcount))
	{
		printf("Error: the map is not closed!\n");
        double_free(map);
        close(fd);
        close(fd2);
		return (1); // print something
	}
    if (!player_haaadar(map))  ////////////////////
    {
        printf("Error\nNo player on the map\n");
        double_free(map);
        return (1);
    }
    double_free(map);
    close(fd);
    close(fd2);
	return (0);
}


char **strdup_map(int fd, int lcount)
{
	int i;
	char **new;
    char *line;

	int count = lcount;
    
	new = malloc(sizeof(char *) * (count + 1));
	if (!new)  // printf("Error: malloc!!\n"),
		return (NULL);
    line = get_first_line(fd);
    i = 0;
    while (i < count)
    {
        if (line)
            new[i] = dup_mline(line);
        line = get_next_line(fd);
        i++;
    }
    new[i] = NULL;
	return (new);
}

char *dup_mline(char *line)
{
    int i;
    int len;
    char *new;

    i = 0;
    len = ft_strlen(line) + 1;

    new = malloc(sizeof(char) * len);
    if (!new)
        return (NULL);
    while (i < len && line[i])
    {
        if (line[i] == '\n')
        {
            new[i] = '\0';
            break;
        }
        else
            new[i] = line[i];
        i++;
    }
    free(line); //// // /
    return (new);
}

char *get_first_line(int fd)
{
    int		i;
	char	*line;

	line = get_next_line(fd);

	while (line)
	{
        i = 0;
        while (line[i])
        {
		    if (line[i] && (line[i] == '0' || line[i] == '1'))
            {
                if (line[i + 1] && (line[i + 1] == '0' || line[i + 1] == '1'))
			    return (line);
            }
            i++;
        }
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

/////////////////////

bool player_haaadar(char **map) // 0 if no player
{
    int i;
    int j;
    int flag;

    i = 0;
    flag = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (is_player_char(map[i][j]))
            {
                flag = 1;
            }
            j++;
        }
        i++;
    }
    if (flag)
        return (1);
    return (0);
}

bool is_player_char(char c)
{
    if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
        return (1);
    return (0);
}