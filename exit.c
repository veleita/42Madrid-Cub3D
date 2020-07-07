/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:01 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/07 20:01:56 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_all(t_var *var)
{
	free(var->file->map->camera);
	while (var->file->map->num_sprites-- > 0)
	{
		free(var->file->map->sprite[var->file->map->num_sprites]);
	}
	free(var->file->map->sprite);
	while (var->file->map->y >= 0)
	{
		free(var->file->map->map[var->file->map->y]);
		var->file->map->y--;
	}
	mlx_destroy_image(var->id->mlx, var->images->screen->id);
	free(var->images->screen);
	free(var->file->map->map);
	free(var->file->map);
	mlx_destroy_image(var->id->mlx, var->images->north->id);
	mlx_destroy_image(var->id->mlx, var->images->south->id);
	mlx_destroy_image(var->id->mlx, var->images->west->id);
	mlx_destroy_image(var->id->mlx, var->images->east->id);
	mlx_destroy_image(var->id->mlx, var->images->sprite->id);
	free(var->images->north);
	free(var->images->south);
	free(var->images->east);
	free(var->images->west);
	free(var->images->sprite);
	free(var->images);
	free(var->spr_ray->wall_z);
	free(var->spr_ray->sprite_order);
	free(var->spr_ray);
	free(var->ray);
	free(var->file->params->no);
	free(var->file->params->so);
	free(var->file->params->ea);
	free(var->file->params->we);
	free(var->file->params->sprt);
	free(var->file->params);
	free(var->file);
	free(var->key);
	mlx_destroy_window(var->id->mlx, var->id->win);
	free(var->id->mlx);
	free(var->id);
	free(var);
}

void ft_exit_fail(char *error)
{
  write(1, error, ft_strlen(error));
  write(1, "\n", 1);
  exit(EXIT_FAILURE);
}

int ft_exit_success(t_var *var)
{
	char *farewell;

	farewell = "Goodbye!\n";
  write(1, farewell, 9);
  free_all(var);
  exit(EXIT_SUCCESS);
  return (1);
}
