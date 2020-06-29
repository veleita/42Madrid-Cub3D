#include "cub3D.h"

void	render(t_file *file, t_ray *ray, t_images *images, 
		t_sprite_ray *s_ray)
{
	int	x;

	x = -1;
	while (++x < file->params->resolution_x)
	{
		get_side_dist(x, (double)file->params->resolution_x, ray,
				file->map->camera);
		get_hit(ray, file->map->map, file->map->x, file->map->y);
		get_wall(ray, file->map->camera, images);
		get_wall_dist(ray, file->map->camera, s_ray, x);
		get_wall_height(ray, file->params);
		get_texture_x(ray);
		print_column(x, ray, file->params, images);
	}
}

int		actualize(t_var *var)
{
	if (var->key->w == 1)
		vertical_movement(var->file->map, var->mov_speed,
				var->file->map->camera->dir_x,
				var->file->map->camera->dir_y);
	if (var->key->s == 1)
		vertical_movement(var->file->map, var->mov_speed,
				-var->file->map->camera->dir_x,
				-var->file->map->camera->dir_y);
	if (var->key->a == 1)
		horizontal_movement(var->file->map, var->mov_speed,
				-var->file->map->camera->plane_x,
				-var->file->map->camera->plane_y);
	if (var->key->d == 1)
		horizontal_movement(var->file->map, var->mov_speed,
				var->file->map->camera->plane_x,
				var->file->map->camera->plane_y);
	if (var->key->left == 1)
		rotation(var->file->map->camera, var->rotate_speed);
	if (var->key->right == 1)
		rotation(var->file->map->camera, -var->rotate_speed);
	order_sprites(var->spr_ray->sprite_order, var->file->map);
	render(var->file, var->ray, var->images, var->spr_ray);
	render_sprites(var);
	return (1);
}
