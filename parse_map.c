#include "cub3D.h"

// FUNCTIONS TO COUNT SPRITES WOULD GO IN THIS FILE

/* The bitmap should be at the bottom of the file, so by the time
** the program finds it, all the other parameters should’ve already
** been parsed and registered.
** If not specified, the default rgb values for the floor and the
** ceiling are (0, 0, 0) 
*/
void	all_parameters(t_file *file)
{
  if (file->resolution_x == 0 || file->resolution_y == 0 ||
      file->no == 0 || file->so == 0 || file->ea == 0 || file->we == 0
      || file->sprt == 0)
    ft_exit("Missing parameters in the map file");
}

/* 
** - Reads every line until EOF (when read == 0) 
** - Checks for incorrect elements in the map
** - Records the length of the longest line in 
** - Counts the number of lines
*/
void	get_map_dimensions(char *line, int fd, short read, t_map *map)
{
  int x_copy;

  while (read > 0)
    {
      x_copy = 0;
      while (line[x_copy] != '\0')
	{
	  if (!(line[x_copy] == ' ' || line[x_copy] == '1' ||
		line[x_copy] == '0' || line[x_copy] == '2' ||
		line[x_copy] == 'N' || line[x_copy] == 'S' ||
		line[x_copy] == 'E' || line[x_copy] == 'W'))
	    ft_exit("Invalid elements in the bitmap");
	  x_copy++;
	}
      map->x = x_copy > map->x ? x_copy : map->x;
      map->y++;
      read = get_next_line(fd, &line);
    }
}

static t_camera	*set_dir_plane(double dirX, double dirY,
			      double planeX, double planeY)
{
	t_camera *camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		exit(0);
	camera->dir_x = dirX;
	camera->dir_y = dirY;
	camera->plane_x = planeX;
	camera->plane_y = planeY;
	return (camera);
}

t_camera	*check_coord(char coord, int pos_x, int pos_y)
{
	t_camera *camera;

	if (coord == 'N')
		camera = set_dir_plane(0, -1, 0.66, 0);
	if (coord == 'S')
		camera = set_dir_plane(0, 1, -0.66, 0);
	if (coord == 'E')
		camera = set_dir_plane(1, 0, 0, -0.66);
	if (coord == 'W')
		camera = set_dir_plane(-1, 0, 0, 0.66);
	camera->pos_x = pos_x + 0.5;
	camera->pos_y = pos_y + 0.5;
	return (camera);
}
