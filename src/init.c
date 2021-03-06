/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:15:20 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/13 16:25:20 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void				init_values_file(t_file *file)
{
	file->map->x = 0;
	file->map->y = 0;
	file->map->map_line = 0;
	file->map->num_sprites = 0;
	file->params->resolution_x = 0;
	file->params->resolution_y = 0;
	file->params->no = 0;
	file->params->so = 0;
	file->params->ea = 0;
	file->params->we = 0;
	file->params->sprt = 0;
}

static t_texture	*create_texture(void *mlx, char *path)
{
	t_texture	*texture;

	if (!(texture = (t_texture*)malloc(sizeof(t_texture))))
		ft_exit_fail("Couldn't allocate t_texture (init.c)");
	if (!(texture->id = mlx_xpm_file_to_image(mlx, path,
					&texture->width, &texture->height)))
		ft_exit_fail("Couldn't charge texture, invalid path (init.c)");
	texture->addr = (int*)mlx_get_data_addr(texture->id, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (texture);
}

static t_images		*create_images(void *mlx, t_parameters *params)
{
	t_images	*images;

	if (!(images = (t_images*)malloc(sizeof(t_images))))
		ft_exit_fail("Couldn't allocate t_images (init.c)");
	if (!(images->screen = (t_screen*)malloc(sizeof(t_screen))))
		ft_exit_fail("Failed to allocate t_screen (init.c)");
	if (!(images->screen->id = mlx_new_image(mlx, params->resolution_x,
					params->resolution_y)))
		ft_exit_fail("Failed to create image (init.c)");
	images->screen->addr = (int*)mlx_get_data_addr(images->screen->id,
			&images->screen->bpp, &images->screen->size_line,
			&images->screen->endian);
	ft_bzero(images->screen->addr,
			(params->resolution_x * params->resolution_y));
	images->north = create_texture(mlx, params->no);
	images->south = create_texture(mlx, params->so);
	images->east = create_texture(mlx, params->ea);
	images->west = create_texture(mlx, params->we);
	images->sprite = create_texture(mlx, params->sprt);
	return (images);
}

void				init_values_render(t_var *var)
{
	var->key->a = 0;
	var->key->w = 0;
	var->key->s = 0;
	var->key->d = 0;
	var->key->left = 0;
	var->key->right = 0;
	var->key->esc = 0;
	var->mov_speed = 0.05;
	var->rotate_speed = 0.02;
	ft_bzero(var->spr_ray->sprite_order, var->file->map->num_sprites);
	ft_bzero(var->spr_ray->wall_z, var->file->params->resolution_x);
}

void				init(const char *file_name, t_var *var)
{
	var->file = read_file(file_name);
	if (!var->file->map->map)
		ft_exit_fail("No bitmap encountered");
	if (!(var->id = (t_id*)malloc(sizeof(t_id))))
		ft_exit_fail("Failed to allocate t_id (init.c)");
	if (!(var->id->mlx = mlx_init()))
		ft_exit_fail("Failed to establish mlx (init.c)");
	if (!(var->ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_exit_fail("Couldn't allocate memory for ray struct");
	var->spr_ray = (t_sprite_ray*)malloc(sizeof(t_sprite_ray));
	if (var->spr_ray == 0)
		ft_exit_fail("Couldn't allocate memory for ray struct");
	var->spr_ray->sprite_order =
		(int*)malloc(var->file->map->num_sprites * sizeof(int));
	var->spr_ray->wall_z =
		(double*)malloc(var->file->params->resolution_x *
				sizeof(double));
	if (!(var->spr_ray->sprite_order && var->spr_ray->wall_z))
		ft_exit_fail("Couldn't allocate memory for sprite arrays");
	var->images = create_images(var->id->mlx, var->file->params);
	if (!(var->key = (t_key*)malloc(sizeof(t_key))))
		ft_exit_fail("Oops error allocating t_key (init.c)");
}
