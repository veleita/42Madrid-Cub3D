#include "cub3D.h"

/* 
** L12: Checks that no resolution values have already been registered
** L14: Iterates through the spaces between the identifier ’R’ and the
** 	resolution values.
** L26: Sets the minimum resolution value to 50x50
** L28: Sets the maximum resolution value to 2560x1440
*/
static void	get_resolution(char *line, t_file *file, int it)
{
  if (file->resolution_x != 0 || file->resolution_y != 0)
    ft_exit("Found more than one resolution value");
  remove_space(line, &it);
  while (ft_isdigit(line[it]))
    {
      file->resolution_x = file->resolution_x * 10 + line[it] - '0';
      it++;
    }
  it++;
  while (ft_isdigit(line[it]))
    {
      file->resolution_y = file->resolution_y * 10 + line[it] - '0';
      it++;
    }
  file->resolution_x = file->resolution_x < 50 ? 50 : file->resolution_x;
  file->resolution_y = file->resolution_y < 50 ? 50 : file->resolution_y;
  file->resolution_x = file->resolution_x > 2560 ? 2560 : file->resolution_x;
  file->resolution_y = file->resolution_y > 1440 ? 1440 : file->resolution_y;
}

/*
** L42: Reads everyting in the line that is not a space, len - it would be
**	the number of characters in the path 
*/
static char	*get_path(char *line, int it)
{
  char *ret;
  int  len;

  remove_space(line, &it);
  len = it;
  while (!(line[len] == ' ' || line[len] == '\0'))
    len++;
  if (!(ret = (char*)malloc(len - it + 1)))
    ft_exit("Failed to allocate path when reading the map file");
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

static t_color	get_color(char *line, int it)
{
  t_color ret;

  //if (!(ret = (t_color*)malloc(sizeof(t_color))))
  //ft_exit("Couldn't allocate memory for t_color struct");
  ret.r = 0;
  ret.g = 0;
  ret.b = 0;
  remove_space(line, &it);
  while (ft_isdigit(line[it++]))
    ret.r = ret.r * 10 + line[it - 1] - '0';
  while (ft_isdigit(line[it++]))
    ret.g = ret.g * 10 + line[it - 1] - '0';
  while (ft_isdigit(line[it++]))
    ret.b = ret.b * 10 + line[it - 1] - '0';
  if (ret.r > 255 || ret.g > 255 || ret.b > 255 ||
      ret.r < 0 || ret.g < 0 || ret.b < 0)
    ft_exit("Invalid rgb values");
  return (ret);
}

/* 
** L90: Note that line[it] is the first character in the line after the
** 	spaces, trimmed by the remove_spaces function
*/
static void	parse_parameters(char *line, int len, int fd,
				 t_file *file)
{
  int it;

  it = 0;
  remove_space(line, &it);
  if (line[it] == 'R')
    get_resolution(line, file, it + 1);      
  else if (line[it] == 'N' && line[it + 1] == 'O')
    file->no = get_path(line, it + 2);
  else if (line[it] == 'S' && line[it + 1] == 'O')
    file->so = get_path(line, it + 2);
  else if (line[it] == 'W' && line[it + 1] == 'E')
    file->we = get_path(line, it + 2);
  else if (line[it] == 'E' && line[it + 1] == 'A')
    file->ea = get_path(line, it + 2);
  else if (line[it] == 'S' && line[it + 1] == ' ')
    file->sprt = get_path(line, it + 1);
  else if (line[it] == 'F')
    file->floor_rgb = get_color(line, it + 1);
  else if (line[it] == 'C')
    file->ceiling_rgb = get_color(line, it + 1);
  else if (line[it] == '1')
    {
      all_parameters(file);
      read_map(line, fd, len, file->map);
    }
  free(line);
}

/*
** L125: Store the map file into the file descriptor (fd)
** L133: Initializes values
*/
t_file		*init_file(const char *file_name)
{
  t_file *file;
  char	*line;
  int	len;
  int	fd;

  if ((fd = open(file_name, O_RDONLY)) == -1)
    ft_exit("Invalid file (read_file.c)");
  if (!(file = (t_file*)malloc(sizeof(t_file))))
    ft_exit("Couldn't allocate memory for file struct (read_file.c)");
  if (!(file->map = (t_map*)malloc(sizeof(t_map))))
    ft_exit("Couldn't allocate memory for map struct (read_file.c)");
  file->map->file_name = file_name;
  file->map->map_line = 0;
  file->map->map_line = 0;
  file->resolution_x = 0;
  file->resolution_y = 0;
  file->no = 0;
  file->so = 0;
  file->ea = 0;
  file->we = 0;
  file->sprt = 0;
  while ((len = get_next_line(fd, &line)) > 0 && ++file->map->map_line)
      parse_parameters(line, len, fd, file);
  free(line);
  return (file);
}
