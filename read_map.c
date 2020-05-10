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
	  map->map[y][x] = line[it] - '0';
      else
	{
	  map->map[y][x] = 0;
	  if (ft_isalpha(line[it]))
	    {
	      if (*player == 1)
		ft_exit("The program found more than one player");
	      map->camera = check_coord(line[it], x, y);
	      *player = 1;
	    }
	}
      it += (line[it] != '\0') ? 1 : 0;
      x++;
    }
  free(line);
}

static void	charge_map(t_map *map)
{
  int	y;

  if (!(map->map = (int**)malloc(map->y * sizeof(int*))))
    ft_exit("Failed to allocate memory for the bitmap");
  y = 0;
  while (y < map->y)
    {
      if (!(map->map[y] = (int*)malloc(map->x * sizeof(int))))
	{
	  free(map->map);
	  ft_exit("Couldn't allocate memory for the bitmap");
	}
      y++;
    }
}

void		read_map(char *line, int fd, int len, t_map *map)
{
  short	player;
  char	*line_2;
  int	y;

  map->x = 0;
  map->y = 0;
  get_map_dimensions(line, fd, len, map);
  close(fd);
  charge_map(map);
  if ((fd = open(map->file_name, O_RDONLY)) == -1)
    ft_exit("Couldn't open file (read_map.c)");
  //if (!(line_2 = (char**)malloc(sizeof(char*))))
  //  ft_exit("Couldn't allocate memory for line (read_map.c)");
  player = 0;
  line_2 = 0;
  while (map->map_line-- > 0)
    get_next_line(fd, &line_2);
  y = -1;
  while (++y < map->y)
    {
      fill_map(line_2, y, map, &player);
      get_next_line(fd, &line_2);
    }
  free(line_2);
  valid_map(map, (int)map->camera->pos_y, (int)map->camera->pos_x);
}
