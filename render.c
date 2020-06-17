#include "cub3D.h"

void	render(t_parameters *parameters, t_camera *camera, int **map,
	       t_texture *texture)
{
  int	x;
  t_ray *ray;

  if (!(ray = (t_ray*)malloc(sizeof(t_ray))))
    ft_exit("Couldn't allocate memory for ray struct");
  ray->map_x = (int)camera->pos_x;
  ray->map_y = (int)camera->pos_y;
  x = -1;
  while (++x < parameters->resolution_x)
    {
      get_side_dist(x, (double)parameters->resolution_x, ray, camera);
      get_hit(ray, map);
      get_wall(ray, camera, parameters, texture);
      get_wall_dist(ray, camera);
      get_wall_height(ray, parameters);
      //      print_column();
    }
}
