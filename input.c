#include "cub3D.h"

int		key_pressed(int keycode, t_key *key)
{
  if (keycode == A_KEY)
    key->a = 1;
  if (keycode == W_KEY)
    key->w = 1;
  if (keycode == S_KEY)
    key->s = 1;
  if (keycode == D_KEY)
    key->d = 1;
  if (keycode == LEFT_KEY)
    key->left = 1;
  if (keycode == RIGHT_KEY)
    key->right = 1;
  return (1);
}

int		key_released(int keycode, t_key *key)
{
  if (keycode == A_KEY)
    key->a = 0;
  if (keycode == W_KEY)
    key->w = 0;
  if (keycode == S_KEY)
    key->s = 0;
  if (keycode == D_KEY)
    key->d = 0;
  if (keycode == LEFT_KEY)
    key->left = 0;
  if (keycode == RIGHT_KEY)
    key->right = 0;
  if (keycode == ESC_KEY)
    ft_exit("Goodbye!");
  return (1);
}

int		move_player(t_var *var)
{
  double	movement_speed;
  double	rotation_speed;

  movement_speed = 0.3;
  rotation_speed = 0.15;
  if (var->key->w == 1)
    vertical_movement(var->file->map, movement_speed,
		      var->file->map->camera->dir_x,
		      var->file->map->camera->dir_y);
  if (var->key->s == 1)
    vertical_movement(var->file->map, movement_speed,
		      -var->file->map->camera->dir_x,
		      -var->file->map->camera->dir_y);
  if (var->key->a == 1)
    horizontal_movement(var->file->map, movement_speed,
			-var->file->map->camera->plane_x,
			-var->file->map->camera->plane_y);
  if (var->key->d == 1)
    horizontal_movement(var->file->map, movement_speed,
			var->file->map->camera->plane_x,
			var->file->map->camera->plane_y);
  if (var->key->left)
    rotation(var->file->map->camera, rotation_speed);
  if (var->key->right)
    rotation(var->file->map->camera, -rotation_speed);
  render(var->file, var->mlx, var->win, var->images);
  return (1);
}
