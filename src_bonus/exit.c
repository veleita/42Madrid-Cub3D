/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:01 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/17 01:08:35 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		free_all(t_var *var)
{
	if (var->spr_ray)
		free_spr_ray(var->spr_ray);
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
}

t_var		*get_var(void)
{
	static t_var var;

	return (&var);
}

void		ft_exit_fail(char *error)
{
	t_var	*var;

	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	var = get_var();
	free_all(var);
	system("pkill play");
	exit(EXIT_FAILURE);
}

int			ft_exit_success(t_var *var)
{
	char *farewell;

	farewell = "Goodbye!\n";
	write(1, farewell, 9);
	free_all(var);
	system("pkill play");
	exit(EXIT_SUCCESS);
	return (1);
}
