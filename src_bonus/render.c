/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:16:15 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/17 01:17:17 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		render(t_file *file, t_ray *ray, t_images *images,
		t_sprite_ray *s_ray)
{
	int	x;

	x = -1;
	while (++x < file->params->resolution_x)
	{
		get_side_dist(x, (double)file->params->resolution_x, ray,
				file->map->camera);
		get_hit(ray, file->map->map, file->map->y);
		get_wall(ray, file->map->camera, images);
		get_wall_dist(ray, file->map->camera, s_ray, x);
		get_wall_height(ray, file->params);
		get_texture_x(ray);
		print_column(x, ray, file->params, images);
	}
}

static void	trigger_events(t_var *var)
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
	if (var->key->esc == 1)
		ft_exit_success(var);
}

int			actualize(t_var *var)
{
	trigger_events(var);
	jump(var->key, var->ray);
	crouch(var->key, var->ray);
	up_down(var->key, var->ray);
	order_sprites(var->spr_ray->sprite_order, var->file->map);
	render(var->file, var->ray, var->images, var->spr_ray);
	render_sprites(var);
	mlx_put_image_to_window(var->id->mlx, var->id->win,
			var->images->screen->id, 0, 0);
	return (1);
}
