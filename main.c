/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 10:58:32 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/01 17:54:55 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 ** L24: init() initializates main variables
 **
 ** Event hooks info
 ** https://harm-smits.github.io/42docs/libs/minilibx/events.html
 **
 ** L25: KEY INPUT
 ** These are called constantly while a key is being pressed (2 code)
 ** or constantly while a key is being released (3 code) 
 **
 ** L27: MOVEMENT LOOP
 ** 	This one is called constantly 
 **
 ** L28: CLOSE THE WINDOW
 ** 	The destroy notify event (17 code) notifies that a window is closed
 ** 	https://tronche.com/gui/x/xlib/events/window-state-change/destroy.html
 **
 ** L29: KEEP THE PROGRAM RUNNING
 */
void	game_option(t_var *var)
{
	var->id->win = mlx_new_window(var->id->mlx,
			var->file->params->resolution_x,
			var->file->params->resolution_y,
			"cub3D");
	if (var->id->win == NULL)
		ft_exit_fail("Failed to open new window (init.c)");
	zero_values(var);
	mlx_hook(var->id->win, 17, 0L, &ft_exit_success, var->key);
	mlx_hook(var->id->win, 2, 1L<<0, &key_pressed, var->key);
	mlx_hook(var->id->win, 3, 1L<<1, &key_released, var->key);
	mlx_loop_hook(var->id->mlx, &actualize, var);
	mlx_loop(var->id->mlx);
}

void	screenshot_option(t_var *var)
{
	render(var->file, var->ray, var->images, var->spr_ray);
	order_sprites(var->spr_ray->sprite_order, var->file->map);
	render_sprites(var);
	create_bmp(var->file->params, var->images->screen->addr);
}

int main(int argc, char **argv)
{
	t_var *var;

	if (!(argc == 2 || argc == 3))
		ft_exit_fail("Wrong number of arguments (main.c)");
	if (!(var = (t_var*)malloc(sizeof(t_var))))
		ft_exit_fail("Failed to allocate memory for t_var (main.c)"); 
	init(argv[1], var);
	if (argc == 2)
	{
		game_option(var);
	}
	else if (argc == 3 && ft_strcmp(argv[2], "--save") == 1)
	{
		screenshot_option(var);
	}
	else
		ft_exit_fail("Invalid argument (main.c)");
}
