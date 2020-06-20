#include "cub3D.h"

void	render(t_file *file, void *mlx, t_images *images)
{
  int	x;
  t_ray *ray;

  if (!(ray = (t_ray*)malloc(sizeof(t_ray))))
    ft_exit("Couldn't allocate memory for ray struct");
  ray->map_x = (int)file->map->camera->pos_x;
  ray->map_y = (int)file->map->camera->pos_y;
  x = -1;
  while (++x < file->params->resolution_x)
    {
      get_side_dist(x, (double)file->params->resolution_x, ray,
		    file->map->camera);
      get_hit(ray, file->map->map, file->map->x, file->map->y);
      get_wall(ray, file->map->camera, file->params, images->texture);
      get_wall_dist(ray, file->map->camera);
      get_wall_height(ray, file->params);
      get_texture_addr(images->texture, mlx);
      get_texture_x(ray, images->texture);
      print_column(x, ray, file->params, images);
      mlx_destroy_image(mlx, images->texture->id);
    }
}
