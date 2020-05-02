#include "cub3D.h"

void	charge_map(char *line, t_map *map)
{
  int	**map;
  int	fd;
  int	x;
  int	player;

  // I’ve noted that an int** array maybe is way too big for
  // a map which only contains values from 0 to 5, it may
  // be a good idea to make it a short** array instead
  if (!(map = (int**)malloc(x * sizeof(int*))))
    ft_exit("Failed to allocate memory for the bitmap");
  fd = open(map->file_name, O_RDONLY);
  line = 0;
  player = 0;
  x = map->x - 1;
  while (x >= 0)
    {
      get_next_line(fd, &line);
      if (!(map[x] = (int*)malloc(map->y * sizeof(int))))
	{
	  free(map);
	  ft_exit("Couldn't allocate memory for the bitmap");
	}
      fill_map(line, x, map, &player);
      x--;
    }
}

void	fill_map(char *line, int x, t_map *map, short *player)
{
  int y;
  y = 0;
  while (*line != '\0')
    {
      if (ft_isdigit(*line))
	{
	  map[x][y] = *line - '0';
	  y++;
	}
      else
	{
	  map[x][y] = 0;
	  if (isalpha(*line))
	    {
	      if (*player == 1)
		ft_exit("The program found more than one player");
	      map->camera = check_coord(*line, x, y);
	      *player = 1;
	    }
	}
    }
}

void	read_map(char *line, int fd, int len, t_map *map)
{
  // Would this work?
  // *map = (t_map)malloc(t_map)
  if (!(map = (t_map*)malloc(t_map)))
    ft_exit("Couldn't allocate memory for the map struct(read_map.c)");
  get_map_dimensions(line, fd, len, map);
  charge_map(line, map);
}
