/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:15:33 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/17 19:59:59 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		manage_map(char *line, int len, int fd, t_file *file)
{
	all_parameters(file->params);
	read_map(line, fd, len, file->map);
}

static short	parse_textures(int it, char *line, t_file *file)
{
	if (line[it] == 'N' && line[it + 1] == 'O' && file->params->no == 0)
		file->params->no = get_path(line, it + 2);
	else if (line[it] == 'S' && line[it + 1] == 'O' && file->params->so == 0)
		file->params->so = get_path(line, it + 2);
	else if (line[it] == 'W' && line[it + 1] == 'E' && file->params->we == 0)
		file->params->we = get_path(line, it + 2);
	else if (line[it] == 'E' && line[it + 1] == 'A' && file->params->ea == 0)
		file->params->ea = get_path(line, it + 2);
	else
		return (0);
	return (1);
}

static short	parse_colors(int it, char *line, t_file *file)
{
	static short	f_color;
	static short	c_color;

	if (line[it] == 'F' && f_color != 1)
	{
		file->params->floor_rgb = get_color(line, it + 1);
		f_color = 1;
	}
	else if (line[it] == 'C' && c_color != 1)
	{
		file->params->ceiling_rgb = get_color(line, it + 1);
		c_color = 1;
	}
	else
		return (0);
	return (1);
}

void		parse_parameters(char *line, int len, int fd, t_file *file)
{
	int	it;

	it = 0;
	remove_space(line, &it);
	if (line[it] == 'R' && file->params->resolution_x == 0 &&
			file->params->resolution_y == 0)
		get_resolution(line, file->params, it + 1);
	else if (parse_textures(it, line, file) == 1)
		it = it;
	else if (parse_colors(it, line, file) == 1)
		it = it;
	else if (line[it] == 'S' && line[it + 1] == ' ' && file->params->sprt == 0)
		file->params->sprt = get_path(line, it + 1);
	else if (line[it] == 'M')
	{
		file->params->music = get_path(line, it + 1);
		printf("%s\n", file->params->music);
	}
	else if (line[it] == '1')
		return (manage_map(line, len, fd, file));
	else if (line[it] != '\0')
		ft_exit_fail("Invalid element in the configuration file");
	free(line);
}

t_file		*read_file(const char *file_name)
{
	t_file	*file;
	char	*line;
	int		len;
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		ft_exit_fail("Invalid file (read_file.c)");
	if (!(file = (t_file*)malloc(sizeof(t_file))))
		ft_exit_fail("Couldn't allocate t_file (init.c)");
	if (!(file->map = (t_map*)malloc(sizeof(t_map))))
		ft_exit_fail("Couldn't allocate t_map (init.c)");
	if (!(file->params = (t_parameters*)malloc(sizeof(t_parameters))))
		ft_exit_fail("Couldn't allocate parameters (init.c)");
	file->map->file_name = file_name;
	init_values_file(file);
	while ((len = get_next_line(fd, &line)) > 0 && ++file->map->map_line)
		parse_parameters(line, len, fd, file);
	free(line);
	return (file);
}
