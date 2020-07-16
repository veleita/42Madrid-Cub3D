/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 09:25:17 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/16 09:53:35 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	up_down(t_key *key, t_ray *ray)
{
	short 	width;
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
