/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 09:25:17 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/17 01:10:38 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	up_down(t_key *key, t_ray *ray)
{
	short	width;
	short	speed;

	width = 800;
	speed = 20;
	if (key->down == 1)
	{
		if (ray->up > 0)
			ray->up -= speed;
		else
			ray->down += speed;
		ray->down = ray->down < width ? ray->down : width;
	}
	if (key->up == 1)
	{
		if (ray->down > 0)
			ray->down -= speed;
		else
			ray->up += speed;
		ray->up = ray->up < width ? ray->up : width;
	}
}

void	jump(t_key *key, t_ray *ray)
{
	short	top;
	short	speed;

	top = 800;
	speed = 70;
	if (key->spc == 1 && key->up == 0 && key->down == 0)
	{
		if (ray->down > 0)
			ray->down -= speed;
		else if (ray->up <= top)
			ray->up += speed;
	}
	if (key->spc == 3 && key->up == 0)
	{
		if (ray->up > 0)
			ray->up -= speed;
		else
			key->spc = 0;
	}
}

void	crouch(t_key *key, t_ray *ray)
{
	if (key->c == 1)
	{
		ray->down += 800;
		key->c = -1;
	}
	if (key->c == 2)
	{
		ray->down -= 800;
		key->c = 0;
	}
}
