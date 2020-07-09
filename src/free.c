/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 00:03:51 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/09 12:19:59 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "mlx_int.h"
#include <X11/Xlib.h>

static void	mlx_terminate(void *mlx)
{
	struct s_xvar *xvar;

	xvar = mlx;
	if (xvar->private_cmap)
		XFreeColormap(xvar->display, (Colormap)xvar->private_cmap);
	XCloseDisplay(xvar->display);
	free(xvar);
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

void	free_all(t_var *var)
{
	if (var->spr_ray)
	{
		if (var->spr_ray->wall_z)
			free(var->spr_ray->wall_z);
		if (var->spr_ray->sprite_order)
			free(var->spr_ray->sprite_order);
		free(var->spr_ray);
	}
	if (var->ray)
		free(var->ray);
	if (var->file)
		free_file(var->file);
	if (var->key)
		free(var->key);
	if (var->images)
	{
		destroy_images(var->images, var->id->mlx);
		free_images(var->images);
	}
	if (var->id)
	{
		if (var->id->win)
			mlx_destroy_window(var->id->mlx, var->id->win);
		if (var->id->mlx)
			mlx_terminate(var->id->mlx);
		free(var->id);
	}
}
