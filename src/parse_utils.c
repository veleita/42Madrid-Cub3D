/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:24:09 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/17 17:44:23 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_resolution(char *line, t_parameters *params, int it)
{
	if (params->resolution_x != 0 || params->resolution_y != 0)
		ft_exit_fail("Found more than one resolution value");
	remove_space(line, &it);
	while (line[it] >= '0' && line[it] <= '9')
	{
		params->resolution_x = params->resolution_x * 10 +
			line[it] - '0';
		it++;
	}
	it++;
	while ('0' <= line[it] && line[it] <= '9')
	{
		params->resolution_y = params->resolution_y * 10 +
			line[it] - '0';
		it++;
	}
	params->resolution_x = (params->resolution_x < 200) ?
		200 : params->resolution_x;
	params->resolution_y = (params->resolution_y < 200) ?
		200 : params->resolution_y;
	params->resolution_x = (params->resolution_x > 1900) ?
		1900 : params->resolution_x;
	params->resolution_y = (params->resolution_y > 1440) ?
		1440 : params->resolution_y;
}

char	*get_path(char *line, int it)
{
	char	*ret;
	int		len;

	remove_space(line, &it);
	len = it;
	while (!(line[len] == ' ' || line[len] == '\0'))
		len++;
	if (!(ret = (char*)malloc(len - it + 1)))
		ft_exit_fail("Couldn't allocate path (read_file.c)");
	len = 0;
	while (!(line[it] == ' ' || line[it] == '\0'))
	{
		ret[len] = line[it];
		len++;
		it++;
	}
	ret[len] = '\0';
	return (ret);
}

t_color	get_color(char *line, int it)
{
	t_color	ret;
	short	digits;

	ret.r = 0;
	ret.g = 0;
	ret.b = 0;
	remove_space(line, &it);
	digits = 0;
	while (line[it++] >= '0' && line[it - 1] <= '9' && ++digits)
		ret.r = ret.r * 10 + line[it - 1] - '0';
	digits = (digits > 1 && digits < 5) ? 0 : -1;
	if (digits == -1)
		ft_exit_fail("Invalid rgb");
	while (line[it++] >= '0' && line[it - 1] <= '9' && ++digits)
		ret.g = ret.g * 10 + line[it - 1] - '0';
	digits = (digits > 1 && digits < 5) ? 0 : -1;
	if (digits == -1)
		ft_exit_fail("Invalid rgb");
	while (line[it++] >= '0' && line[it - 1] <= '9' && ++digits)
		ret.b = ret.b * 10 + line[it - 1] - '0';
	digits = (digits > 1 && digits < 5) ? 0 : -1;
	if (digits == -1 || line[it] != '\0')
		ft_exit_fail("Invalid rgb");
	return (ret);
}
