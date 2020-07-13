/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:17:26 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/13 11:36:22 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	ft_strlen(const char *s)
{
	size_t ret;

	if (!s)
		return (0);
	ret = 0;
	while (s[ret] != '\0')
		ret++;
	return (ret);
}

char	*ft_strdup(const char *s1)
{ 
	char	*ret;
	char	*pret;
	char	*ps1;

	ps1 = (char*)s1;
	if ((ret = (char*)malloc(ft_strlen(s1) + 1)))
	{
		pret = ret;
		while (*ps1 != '\0')
			*(pret++) = *(ps1++);
		*pret = '\0';
		return (ret);
	}
	else
		return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*pret;

	if (!(ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	pret = ret;
	while (s1 && *s1)
		*(pret++) = *(s1++);
	while (s2 && *s2)
		*(pret++) = *(s2++);
	*pret = '\0';
	return (ret);
}

short	ft_strchr(char *s, char c)
{
	int	it;

	if (!s)
		return (0);
	it = 0;
	while (s[it])
	{
		if (s[it++] == c)
			return (it);
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	char	*pret;
	size_t	retlen;
	size_t	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (slen < start)
		return (ft_strdup(""));
	retlen = slen - start > len ? len : slen - start;
	if (!(ret = (char*)malloc(sizeof(char) * (retlen + 1))))
		return (0);
	pret = ret;
	while (retlen-- > 0)
		*(pret++) = s[start++];
	*pret = '\0';
	return (ret);
}
