#include "cub3D.h"

/* This version of the gnl function can only read from 10 file
** descriptors at once, which is more that enough for the purposes
** of this project.
** Also, the buffer size for this version will be fixed to 80,
** based on the assumption that most of our maps won’t have lines
** longer than 80 characters. So the function can run faster without
** consumming an excesive amount of memory in the buffer allocation.
** Some additional enhancements have also been added, like the
** supression of the "empty" auxiliar function and some expendable
** variables in the utils functions.
*/
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

short	get_next_line(int fd, char **line)
{
  char		*buffer;
  static char	*file[10];
  int		len;
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
