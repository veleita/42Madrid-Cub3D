#include "cub3D.h"

void	 remove_space(char *line, int *it)
{
  while (line[*it] == ' ' || line[*it] == '\f' || line[*it] == '\t')
    (*it)++;
}

short 	ft_strcmp(const char *s1, const char *s2)
{
  while (*s1 || *s2)
    {
      if ((unsigned char)*s1 != (unsigned char)*s2)
	return ((unsigned char)*s1 - (unsigned char)*s2);
      s1++;
      s2++;
    }
  return (0);
}

size_t	 ft_strlen(const char *s)
{
  size_t ret;

  /* The function returns 0 if the string is null */
  if (!s)
    return (0);
  ret = 0;
  while (s[ret] != '\0')
    ret++;
  return (ret);
}

char	 *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
  size_t	iterator;

  /* The function returns a null string if haystack is null */
  if (haystack == 0)
    return (0);
  /* The function returns the haystack string if the first character
   * in needle is ’\0’ */
  if (*needle == '\0')
    return ((char*)haystack);
  while (*haystack != '\0' && len > 0)
    {
      iterator = 0;
      while (haystack[iterator] == needle[iterator] && iterator <= len)
	{
	  iterator++;
	}
      if (needle[iterator] == '\0')
	return ((char *)haystack);
      haystack++;
    }
  return (0);
}

void 	ft_bzero(void *s, size_t n)
{
  char *ps;

  ps = (char*)s;
  while (n-- > 0)
    *(ps++) = 0;
}

short 	ft_isdigit(int c)
{
  return (('0' <= c && c <= '9')? 1 : 0);
}

short 	ft_isalpha(int c)
{
  return ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) ? 1 : 0);
}
