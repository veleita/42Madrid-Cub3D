#include "cub3D.h"

static void	fill_map(char *line, int y, t_map *map, short *player)
{
  int x;
  int it;
  it = 0;
  x = 0;
  while (x < map->x)
    {
      if (ft_isdigit(line[it]))
	  map->map[x][y] = line[it] - '0';
      else
	{
	  map->map[x][y] = 0;
	  if (ft_isalpha(line[it]))
	    {
	      if (*player == 1)
		ft_exit("The program found more than one player");
	      map->camera = check_coord(*line, x, y);
	      *player = 1;
	    }
	}
      it++;
      x++;
    }
}

static void	charge_map(t_map *map)
{
  char	**line;
  int	x;

  // I’ve noted that an int** array maybe is way too big for
  // a map which only contains values from 0 to 5, it may
  // be a good idea to make it a short** array instead
  if (!(map->map = (int**)malloc(map->x * sizeof(int*))))
    ft_exit("Failed to allocate memory for the bitmap");
  x = 0;
  while (x < map->x)
    {
      if (!(map->map[x] = (int*)malloc((map->y - 1) * sizeof(int))))
	{
	  free(map->map);
	  ft_exit("Couldn't allocate memory for the bitmap");
	}
      x++;
    }
}

void		read_map(char *line, int fd, int len, t_map *map)
{
  short	player;
  char	**line_2;
  int	y;

  get_map_dimensions(line, fd, len, map);
  close(fd);
  charge_map(map);
  if ((fd = open(map->file_name, O_RDONLY)) == -1)
    ft_exit("Couldn't open file (read_map.c)");
  if (!(line_2 = (char**)malloc(sizeof(char*))))
    ft_exit("Couldn't allocate memory for line (read_map.c)");
  player = 0;
  while (map->map_line-- > 0)
    get_next_line(fd, line_2);
  y = 0;
  while (y < map->y)
    {
      fill_map(*line_2, y, map, &player);
      y++;
      get_next_line(fd, line_2);
    }
  free(line_2);
}
