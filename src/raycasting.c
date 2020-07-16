/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:36 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/17 00:18:37 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_side_dist(int x, double resolution_x, t_ray *ray, t_camera *camera)
{
	ray->camera_x = (2 * x / (double)resolution_x) - 1;
	ray->dir_x = camera->dir_x + (camera->plane_x * ray->camera_x);
	ray->dir_y = camera->dir_y + (camera->plane_y * ray->camera_x);
	ray->map_x = (int)camera->pos_x;
	ray->map_y = (int)camera->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
		ray->side_dist_x = (camera->pos_x - ray->map_x) *
			ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - camera->pos_x) *
			ray->delta_dist_x;
	if (ray->dir_y < 0)
		ray->side_dist_y = (camera->pos_y - ray->map_y) *
			ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - camera->pos_y) *
			ray->delta_dist_y;
}

void	get_hit(t_ray *ray, int **map, int map_max_y)
{
	ray->step_x = (ray->dir_x < 0) ? -1 : 1;
	ray->step_y = (ray->dir_y < 0) ? -1 : 1;
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		ray->map_y = (ray->map_y >= map_max_y) ? map_max_y : ray->map_y;
		if (map[ray->map_y][ray->map_x] == 1)
			ray->hit = 1;
	}
}

void	get_wall(t_ray *ray, t_camera *camera, t_images *images)
{
	if (ray->side == 1)
	{
		ray->wall_hit_x = camera->pos_x + ((ray->map_y - camera->pos_y
					+ (1 - ray->step_y) / 2)
				/ ray->dir_y) * ray->dir_x;
		ray->texture = (ray->dir_y < 0) ? images->south : images->north;
	}
	else
	{
		ray->wall_hit_x = camera->pos_y + ((ray->map_x - camera->pos_x
					+ (1 - ray->step_x) / 2)
				/ ray->dir_x) * ray->dir_y;
		ray->texture = (ray->dir_x < 0) ? images->east : images->west;
	}
	ray->wall_hit_x -= floor(ray->wall_hit_x);
}

void	get_wall_dist(t_ray *ray, t_camera *camera, t_sprite_ray *s_ray, int x)
{
	if (ray->side == 1)
		ray->perp_wall_dist = fabs((ray->map_y - camera->pos_y +
					(1 - ray->step_y) / 2.0) / ray->dir_y);
	else
		ray->perp_wall_dist = fabs((ray->map_x - camera->pos_x +
					(1 - ray->step_x) / 2.0) / ray->dir_x);
	ray->perp_wall_dist *= (ray->perp_wall_dist < 0) ? -1 : 1;
	s_ray->wall_z[x] = ray->perp_wall_dist;
}

void	get_wall_height(t_ray *ray, t_parameters *parameters)
{
	ray->wall_height = (int)(parameters->resolution_y /
			ray->perp_wall_dist);
	ray->draw_start = ((parameters->resolution_y + ray->up - ray->down) / 2) -
		(ray->wall_height / 2);
	ray->draw_start = (ray->draw_start < 0) ? 0 : ray->draw_start;
	ray->draw_end = ((parameters->resolution_y + ray->up - ray->down) / 2) +
		(ray->wall_height / 2);
	ray->draw_end = (ray->draw_end > parameters->resolution_y) ?
		parameters->resolution_y : ray->draw_end;
}
