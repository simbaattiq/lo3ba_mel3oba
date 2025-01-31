


#include <cub3D.h>

bool is_valid_cell(int x, int y, char **map, int map_height)
{
    if (y < 0 || y >= map_height)
    {
        return (false); // y is out of bounds
    }

    if (x < 0 || x >= (int)ft_strlen(map[y]))
    {
        return (false); // x is out of bounds
    }
    return (true);
}

bool map_closed(char **map, int map_height) 
{
    int y;
    int x;


    y = 0;
    while (y < map_height) 
    {
        x = 0;
        while ( x < (int)ft_strlen(map[y])) 
        {
            if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' 
                                || map[y][x] == 'E' || map[y][x] == 'W')
            {
                if (x == 0 || x == (int)ft_strlen(map[y]) - 1 || y == 0 || y == map_height - 1) 
                {
                    return (false);
                }

                if (!is_valid_cell(x, y - 1, map, map_height) || map[y - 1][x] == ' ') 
                    return (false);
                if (!is_valid_cell(x, y + 1, map, map_height) || map[y + 1][x] == ' ') 
                    return (false);
                if (!is_valid_cell(x - 1, y, map, map_height) || map[y][x - 1] == ' ') 
                    return (false);
                if (!is_valid_cell(x + 1, y, map, map_height) || map[y][x + 1] == ' ') 
                    return (false);
            }
            x++;
        }
        y++;
    }
    return (true);
}