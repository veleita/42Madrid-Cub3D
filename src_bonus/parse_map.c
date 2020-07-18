/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:15:56 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/17 16:52:37 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			all_parameters(t_parameters *parameters)
{
	if (parameters->resolution_x == 0 || parameters->resolution_y == 0 ||
			parameters->no == 0 || parameters->so == 0 ||
			parameters->ea == 0 || parameters->we == 0 ||
			parameters->sprt == 0)
		ft_exit_fail("Missing parameters in the map file");
}

int				get_map_dimensions(char *line, int fd, short read, t_map *map)
{
	int	x_copy;

	while (read > 0)
	{
		x_copy = 0;
		while (line[x_copy] != '\0')
		{
			if (!(line[x_copy] == ' ' || line[x_copy] == '1' ||
						line[x_copy] == '0' ||
						line[x_copy] == '2' ||
						ft_isalpha(line[x_copy])))
				ft_exit_fail("Invalid elements in the bitmap");
			map->num_sprites += (line[x_copy] == '2') ? 1 : 0;
			x_copy++;
		}
		map->x = x_copy > map->x ? x_copy : map->x;
		map->y++;
		free(line);
		read = get_next_line(fd, &line);
	}
	map->y--;
	free(line);
	close(fd);
	return (map->num_sprites);
}

static t_camera	*set_dir_plane(double dir_x, double dir_y,
		double plane_x, double plane_y)
{
	t_camera	*camera;

	if (!(camera = (t_camera*)malloc(sizeof(t_camera))))
		exit(0);
	camera->dir_x = dir_x;
	camera->dir_y = dir_y;
	camera->plane_x = plane_x;
	camera->plane_y = plane_y;
	return (camera);
}

t_camera		*check_coord(char coord, int pos_x, int pos_y)
{
	t_camera	*camera;

	if (coord == 'N')
		camera = set_dir_plane(0, -1, 0.66, 0);
	else if (coord == 'S')
		camera = set_dir_plane(0, 1, -0.66, 0);
	else if (coord == 'E')
		camera = set_dir_plane(1, 0, 0, 0.66);
	else if (coord == 'W')
		camera = set_dir_plane(-1, 0, 0, -0.66);
	else
		ft_exit_fail("Invalid elements in the bitmap (parse_map.c)");
	camera->pos_x = pos_x + 0.5;
	camera->pos_y = pos_y + 0.5;
	return (camera);
}

void			valid_map(t_map *map, int y, int x)
{
	if (((map->map[y][x] == 0 || map->map[y][x] == 2) &&
						(x == (map->x - 1) || y == (map->y - 1) ||
						x == 0 || y == 0)) || map->map[y][x] == 4)
		ft_exit_fail("Invalid map");
	map->map[y][x] = map->map[y][x] == 0 ? 3 : 1;
	if (y != (map->y - 1))
		if (map->map[y + 1][x] == 0 || map->map[y + 1][x] == 4)
			valid_map(map, y + 1, x);
	if (y != 0)
		if (map->map[y - 1][x] == 0 || map->map[y - 1][x] == 4)
			valid_map(map, y - 1, x);
	if (x != (map->x - 1))
		if (map->map[y][x + 1] == 0 || map->map[y][x + 1] == 4)
			valid_map(map, y, x + 1);
	if (x != 0)
		if (map->map[y][x - 1] == 0 || map->map[y][x - 1] == 4)
			valid_map(map, y, x - 1);
}
