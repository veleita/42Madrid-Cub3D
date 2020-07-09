#include "cub3D.h"

void	vertical_movement(t_map *map, double movement_speed,
			  double dir_x, double dir_y)
{
  if (map->map[(int)map->camera->pos_y]
		  [(int)(map->camera->pos_x + dir_x * 1)] != 1)
    map->camera->pos_x += dir_x * movement_speed;
  if (map->map[(int)(map->camera->pos_y + dir_y * 1)]
		  [(int)map->camera->pos_x] != 1)
    map->camera->pos_y += dir_y * movement_speed;
}

void	horizontal_movement(t_map *map, double movement_speed,
			    double plane_x, double plane_y)
{
  if (map->map[(int)map->camera->pos_y]
		  [(int)(map->camera->pos_x + plane_x * 1)] != 1)
    map->camera->pos_x += plane_x * movement_speed;
  if (map->map[(int)(map->camera->pos_y + plane_y * 1)]
		  [(int)map->camera->pos_x] != 1)
    map->camera->pos_y += plane_y * movement_speed;
}

void	rotation(t_camera *camera, double rotation_speed)
{
  double dir_y_copy;
  double plane_y_copy;

  dir_y_copy = camera->dir_y;
  camera->dir_y = camera->dir_y * cos(rotation_speed)
    - camera->dir_x * sin(rotation_speed);
  camera->dir_x = dir_y_copy * sin(rotation_speed) + camera->dir_x *
    cos(rotation_speed);
  plane_y_copy = camera->plane_y;
  camera->plane_y = camera->plane_y * cos(rotation_speed) - 
    camera->plane_x * sin(rotation_speed);
  camera->plane_x = plane_y_copy * sin(rotation_speed) + 
    camera->plane_x * cos(rotation_speed);
}
