/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:15:47 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/17 01:09:11 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	charge_sprite(double x, double y, int num_sprites,
		t_sprite **sprite)
{
	if (!(sprite[num_sprites] = (t_sprite*)malloc(sizeof(t_sprite))))
		ft_exit_fail("Didn't allocate sprite[] (read_map.c)");
	sprite[num_sprites]->pos_x = x + 0.5;
	sprite[num_sprites]->pos_y = y + 0.5;
}

static void	map_objects(char number, int x, int y, t_map *map)
{
	map->map[y][x] = number - '0';
	if (number == '2')
		charge_sprite((double)x, (double)y, --map->num_sprites,
				map->sprite);
}

static void	fill_map(char *line, int y, t_map *map, short *player)
{
	int	x;
	int	it;

	it = 0;
	x = -1;
	while (++x < map->x)
	{
		if ('0' <= line[it] && line[it] <= '9')
			map_objects(line[it], x, y, map);
		else
		{
			map->map[y][x] = 0;
			if (ft_isalpha(line[it]))
			{
				if (*player == 1)
					ft_exit_fail("Many players");
				map->camera = check_coord(line[it], x, y);
				*player = 1;
			}
		}
		it += (line[it] != '\0') ? 1 : 0;
	}
	free(line);
}

static void	charge_map(t_map *map, int fd)
{
	int	y;

	if (!(map->sprite = (t_sprite**)malloc(map->num_sprites *
					sizeof(t_sprite*))))
		ft_exit_fail("Couldn't allocate sprites array");
	if (!(map->map = (int**)malloc((map->y + 1) * sizeof(int*))))
		ft_exit_fail("Couldn't allocate bitmap rows");
	y = 0;
	while (y <= map->y)
	{
		if (!(map->map[y] = (int*)malloc(map->x * sizeof(int))))
		{
			free(map->map);
			ft_exit_fail("Couldn't register bitmap col");
		}
		y++;
	}
	if ((fd = open(map->file_name, O_RDONLY)) == -1)
		ft_exit_fail("Error opening file (read_map.c)");
}

void		read_map(char *line, int fd, int len, t_map *map)
{
	short	player;
	char	*line_2;
	int		y;
	int		num_sprites;

	num_sprites = get_map_dimensions(line, fd, len, map);
	charge_map(map, fd);
	player = 0;
	line_2 = 0;
	while (map->map_line-- > 0)
	{
		get_next_line(fd, &line_2);
		if (map->map_line > 0)
			free(line_2);
	}
	y = -1;
	while (++y <= map->y)
	{
		fill_map(line_2, y, map, &player);
		get_next_line(fd, &line_2);
	}
	free(line_2);
	map->num_sprites = num_sprites;
	(player == 0) ? ft_exit_fail("No player nigga") :
		valid_map(map, (int)map->camera->pos_y, (int)map->camera->pos_x);
}
