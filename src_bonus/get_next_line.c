/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:18 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/17 01:06:56 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static short	get_line(char **file, int fd, char **line, int len)
{
	char	*tmp;
	int		it;

	if (len < 0)
		return (-1);
	else if (len == 0 && !file[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	else if ((it = ft_strchr(file[fd], '\n')))
	{
		*line = ft_substr(file[fd], 0, it - 1);
		tmp = ft_strdup(&((file[fd])[it]));
		free(file[fd]);
		file[fd] = tmp;
	}
	else
	{
		*line = ft_strdup(file[fd]);
		free(file[fd]);
		file[fd] = 0;
	}
	return (1);
}

short			get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*file[10];
	int			len;
	char		*tmp;

	if (!line || fd < 0 || !(buffer = (char*)malloc(81)))
		return (-1);
	while ((len = read(fd, buffer, 80)) > 0)
	{
		buffer[len] = '\0';
		if (file[fd] == 0)
			file[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(file[fd], buffer);
			free(file[fd]);
			file[fd] = tmp;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (get_line(file, fd, line, len));
}
