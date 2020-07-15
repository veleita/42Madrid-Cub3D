/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:40:30 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/15 21:04:01 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_headers(unsigned char *file_header,
		unsigned char *info_header, int file_size, t_parameters *params)
{
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(params->resolution_x);
	info_header[5] = (unsigned char)(params->resolution_x >> 8);
	info_header[6] = (unsigned char)(params->resolution_x >> 16);
	info_header[7] = (unsigned char)(params->resolution_x >> 24);
	info_header[8] = (unsigned char)(params->resolution_y);
	info_header[9] = (unsigned char)(params->resolution_y >> 8);
	info_header[10] = (unsigned char)(params->resolution_y >> 16);
	info_header[11] = (unsigned char)(params->resolution_y >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(24);
}

void	create_headers(int fd, int padding, t_parameters *params)
{
	int						file_size;
	static unsigned char	file_header[14];
	static unsigned char	info_header[40];

	ft_bzero(file_header, 14);
	ft_bzero(info_header, 40);
	file_size = 14 + 40 + (3 * params->resolution_x + padding) *
		params->resolution_y;
	write_headers(file_header, info_header, file_size, params);
	write(fd, &file_header, 14);
	write(fd, &info_header, 40);
}

void	write_bmp(int fd, int padding, int *screen, t_parameters *params)
{
	int						i;
	int						j;
	int						color;
	static unsigned char	zero[3];

	ft_bzero(zero, 3);
	i = params->resolution_y - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < params->resolution_x)
		{
			color = screen[i * params->resolution_x + j];
			write(fd, &color, 3);
			j++;
		}
		if (padding > 0)
			write(fd, &zero, padding);
		i--;
	}
}

void	create_bmp(t_parameters *params, int *screen)
{
	int padding;
	int fd;

	padding = (4 - (params->resolution_x * 3) % 4) % 4;
	if ((fd = open("cub3D.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0777)) < 0)
		ft_exit_fail("Couldn't create bitmap (bmp.c)");
	create_headers(fd, padding, params);
	write_bmp(fd, padding, screen, params);
	close(fd);
}
