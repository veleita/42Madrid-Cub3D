/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:01 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/06/30 13:17:03 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_clear(char *error, t_var *var)
{
  free(var);
  // mlx_destroy_window(var->mlx, var->win);
  ft_exit(error);
}

void ft_exit(char *error)
{
  // I may need to free the allocated memory before the exit
  write(1, error, ft_strlen(error));
  write(1, "\n", 1);
  exit(1);
}
