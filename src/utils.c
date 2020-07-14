/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:09 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/13 16:25:45 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	remove_space(char *line, int *it)
{
	while (line[*it] == ' ' || line[*it] == '\f' || line[*it] == '\t')
		(*it)++;
}

void	ft_bzero(void *s, size_t n)
{
	char *ps;

	ps = (char*)s;
	while (n-- > 0)
		*(ps++) = 0;
}

int		ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (0);
	return (1);
}

short	ft_isalpha(int c)
{
	return ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) ? 1 : 0);
}

void	bubble_sort(int *list, double *content, int elements)
{
	int		it;
	int		add;
	int		list_copy;
	double	content_copy;

	it = 0;
	while (it < elements)
	{
		add = it;
		while (++add < elements)
		{
			if (content[it] < content[add])
			{
				list_copy = list[it];
				list[it] = list[add];
				list[add] = list_copy;
				content_copy = content[it];
				content[it] = content[add];
				content[add] = content_copy;
			}
		}
		it++;
	}
}
