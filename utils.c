#include "cub3D.h"

void	 remove_space(char *line, int *it)
{
  while (line[*it] == ' ' || line[*it] == '\f' || line[*it] == '\t')
    (*it)++;
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

void	bubble_sort(int *list, double *content, int elements)
{
	int 	it;
	int 	add;
	int	list_copy;
	double	content_copy;

	it = 0;
	while (it < elements)
	{
		add = it;
		while (++add < elements)
		{
			if ( content[it] > content[add])
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
