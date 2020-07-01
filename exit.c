/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:01 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/01 17:53:53 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_exit_fail(char *error)
{
  write(1, error, ft_strlen(error));
  write(1, "\n", 1);
  exit(EXIT_FAILURE);
}

int ft_exit_success(t_key *key)
{
	char *farewell;

	(void)key;
	farewell = "Goodbye!\n";
  write(1, farewell, 9);
  exit(EXIT_SUCCESS);
  return (1);
}
