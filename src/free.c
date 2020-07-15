/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 00:03:51 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/15 21:04:25 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_spr_ray(t_sprite_ray *spr_ray)
{
	if (spr_ray->wall_z)
		free(spr_ray->wall_z);
	if (spr_ray->sprite_order)
		free(spr_ray->sprite_order);
	free(spr_ray);
}

void	free_map(t_map *map)
{
	if (map->map)
	{
		while (map->y >= 0)
		{
			if (map->map[map->y])
				free(map->map[map->y]);
			map->y--;
		}
		free(map->map);
	}
	if (map->camera)
		free(map->camera);
	while (map->num_sprites-- > 0)
	{
		if (map->sprite)
			free(map->sprite[map->num_sprites]);
	}
	if (map->sprite)
		free(map->sprite);
	free(map);
}

void	free_file(t_file *file)
{
	if (file->params)
	{
		if (file->params->no)
			free(file->params->no);
		if (file->params->so)
			free(file->params->so);
		if (file->params->ea)
			free(file->params->ea);
		if (file->params->we)
			free(file->params->we);
		if (file->params->sprt)
			free(file->params->sprt);
		free(file->params);
	}
	if (file->map)
		free_map(file->map);
	free(file);
}

void	destroy_images(t_images *images, void *mlx)
{
	if (images->screen->id)
		mlx_destroy_image(mlx, images->screen->id);
	if (images->north->id)
		mlx_destroy_image(mlx, images->north->id);
	if (images->south->id)
		mlx_destroy_image(mlx, images->south->id);
	if (images->west->id)
		mlx_destroy_image(mlx, images->west->id);
	if (images->east->id)
		mlx_destroy_image(mlx, images->east->id);
	if (images->sprite->id)
		mlx_destroy_image(mlx, images->sprite->id);
}

void	free_images(t_images *images)
{
	if (images->screen)
		free(images->screen);
	if (images->north)
		free(images->north);
	if (images->south)
		free(images->south);
	if (images->west)
		free(images->west);
	if (images->east)
		free(images->east);
	if (images->sprite)
		free(images->sprite);
	free(images);
}
