/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:01 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/09 12:13:59 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_var	*get_var(void)
{
	static t_var var;

	return (&var);
}

void ft_exit_fail(char *error)
{
	t_var	*var;
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	var = get_var();
	free_all(var);
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
