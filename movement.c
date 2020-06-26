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
  //printf("h");
  if (map->map[(int)map->camera->pos_y]
		  [(int)(map->camera->pos_x + plane_x * 1)] != 1)
    map->camera->pos_x += plane_x * movement_speed;
  if (map->map[(int)(map->camera->pos_y + plane_y * 1)]
		  [(int)map->camera->pos_x] != 1)
    map->camera->pos_y += plane_y * movement_speed;
  //printf("h");
}

void	rotation(t_camera *camera, double rotation_speed)
{
  double dir_x_copy;
  double plane_x_copy;

  dir_x_copy = camera->dir_x;
  camera->dir_x = camera->dir_x * cos(rotation_speed)
    - camera->dir_y * sin(rotation_speed);
  camera->dir_y = dir_x_copy * sin(rotation_speed) + camera->dir_y *
    cos(rotation_speed);
  plane_x_copy = camera->plane_x;
  camera->plane_x = camera->plane_x * cos(rotation_speed) - 
    camera->plane_y * sin(rotation_speed);
  camera->plane_y = plane_x_copy * sin(rotation_speed) + 
    camera->plane_y * cos(rotation_speed);
}
