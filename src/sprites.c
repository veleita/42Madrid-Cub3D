/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:44 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/15 21:06:48 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		order_sprites(int *sprite_order, t_map *map)
{
	double	sprite_distance[map->num_sprites];
	int		it;

	it = 0;
	while (it < map->num_sprites)
	{
		sprite_order[it] = it;
		sprite_distance[it] = (map->camera->pos_x -
				map->sprite[it]->pos_x) *
			(map->camera->pos_x - map->sprite[it]->pos_x) +
			(map->camera->pos_y - map->sprite[it]->pos_y) *
			map->camera->pos_y - map->sprite[it]->pos_y;
		it++;
	}
	bubble_sort(sprite_order, sprite_distance, map->num_sprites);
}

static void	print_stripe(t_sprite_ray *ray, t_images *images,
		t_parameters *params)
{
	int	y;
	int	d;
	int	color;

	ray->tex_x = (int)(256 * (ray->stripe - (-ray->sprite_height / 2
					+ ray->sprite_screen_x)) *
			images->sprite->width / ray->sprite_height) / 256;
	if (ray->transform_y < 0 || ray->transform_y > ray->wall_z[ray->stripe])
		return ;
	y = ray->draw_start_y;
	while (y < ray->draw_end_y)
	{
		d = y * 256 - params->resolution_y *
			128 + ray->sprite_height * 128;
		ray->tex_y = ((d * images->sprite->height) /
				ray->sprite_height) / 256;
		color = images->sprite->addr[images->sprite->width *
			ray->tex_y + ray->tex_x];
		if (color != 0)
			images->screen->addr[y * params->resolution_x +
				ray->stripe] = color;
		y++;
	}
}

static void	calculate_params(t_camera *player, t_sprite_ray *ray,
		t_parameters *params)
{
	ray->transform_x = ray->inv_det * (player->dir_y * ray->sprite_x -
			player->dir_x * ray->sprite_y);
	ray->transform_y = ray->inv_det * (-player->plane_y * ray->sprite_x +
			player->plane_x * ray->sprite_y);
	ray->sprite_screen_x = (int)((params->resolution_x / 2) *
			(1 + ray->transform_x / ray->transform_y));
	ray->sprite_height = abs((int)(params->resolution_y /
				ray->transform_y));
	ray->draw_start_y = params->resolution_y / 2 - ray->sprite_height / 2;
	ray->draw_start_y = (ray->draw_start_y < 0) ? 0 : ray->draw_start_y;
	ray->draw_end_y = params->resolution_y / 2 + ray->sprite_height / 2;
	ray->draw_end_y = (ray->draw_end_y >= params->resolution_y) ?
		params->resolution_y - 1 : ray->draw_end_y;
	ray->draw_start_x = ray->sprite_screen_x - ray->sprite_height / 2;
	ray->draw_start_x = (ray->draw_start_x < 0) ? 0 : ray->draw_start_x;
	ray->draw_end_x = ray->sprite_screen_x + ray->sprite_height / 2;
	ray->draw_end_x = (ray->draw_end_x >= params->resolution_x) ?
		params->resolution_x - 1 : ray->draw_end_x;
}

static void	set_sprite(t_sprite_ray *ray, t_sprite **sprite,
		t_camera *camera, int it)
{
	ray->sprite_x = sprite[ray->sprite_order[it]]->pos_x - camera->pos_x;
	ray->sprite_y = sprite[ray->sprite_order[it]]->pos_y - camera->pos_y;
}

void		render_sprites(t_var *var)
{
	int	it;

	var->spr_ray->inv_det = 1.0 / (var->file->map->camera->plane_x *
			var->file->map->camera->dir_y -
			var->file->map->camera->plane_y *
			var->file->map->camera->dir_x);
	it = -1;
	while (++it < var->file->map->num_sprites)
	{
		set_sprite(var->spr_ray, var->file->map->sprite,
				var->file->map->camera, it);
		calculate_params(var->file->map->camera, var->spr_ray,
				var->file->params);
		var->spr_ray->stripe = var->spr_ray->draw_start_x - 1;
		while (++var->spr_ray->stripe <
				var->spr_ray->draw_end_x)
			print_stripe(var->spr_ray, var->images,
					var->file->params);
	}
}
