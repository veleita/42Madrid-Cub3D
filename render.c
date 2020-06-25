#include "cub3D.h"

void	render(t_file *file, t_id *id, t_ray *ray, t_images *images)
{
  int	x;
  
  x = -1;
  while (++x < file->params->resolution_x)
    {
      get_side_dist(x, (double)file->params->resolution_x, ray,
		    file->map->camera);
      get_hit(ray, file->map->map, file->map->x, file->map->y);
      get_wall(ray, file->map->camera, file->params, images->texture);
      get_wall_dist(ray, file->map->camera);
      get_wall_height(ray, file->params);
      get_texture_addr(images->texture, id->mlx);
      get_texture_x(ray, images->texture);
      print_column(x, ray, file->params, images);
      //      mlx_destroy_image(mlx, images->texture->id);
    }
  mlx_put_image_to_window(id->mlx, id->win, images->screen->id, 0, 0);
}
