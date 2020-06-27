#include "cub3D.h"

/* 
** L12: Checks that no resolution values have already been registered
** L14: Iterates through the spaces between the identifier ’R’ and the
** 	resolution values.
** L28: Sets the minimum resolution value to 50x50
** L32: Sets the maximum resolution value to 2560x1440
*/
static void	get_resolution(char *line, t_parameters *params, int it)
{
  if (params->resolution_x != 0 || params->resolution_y != 0)
    ft_exit("Found more than one resolution value");
  remove_space(line, &it);
  while (ft_isdigit(line[it]))
    {
      params->resolution_x = params->resolution_x * 10 +
	line[it] - '0';
      it++;
    }
  it++;
  while (ft_isdigit(line[it]))
    {
      params->resolution_y = params->resolution_y * 10 +
	line[it] - '0';
      it++;
    }
  params->resolution_x = (params->resolution_x < 50) ?
    50 : params->resolution_x;
  params->resolution_y = (params->resolution_y < 50) ?
    50 : params->resolution_y;
  params->resolution_x = (params->resolution_x > 2560) ?
    2560 : params->resolution_x;
  params->resolution_y = (params->resolution_y > 1440) ?
    1440 : params->resolution_y;
}

/*
** L49: Reads everyting in the line that is not a space, len - it would be
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
** L95: Note that line[it] is the first character in the line after the
** 	spaces, trimmed by the remove_spaces function
*/
void	parse_parameters(char *line, int len, int fd, t_file *file)
{
  int it;

  it = 0;
  remove_space(line, &it);
  if (line[it] == 'R')
    get_resolution(line, file->params, it + 1);      
  else if (line[it] == 'N' && line[it + 1] == 'O')
    file->params->no = get_path(line, it + 2);
  else if (line[it] == 'S' && line[it + 1] == 'O')
    file->params->so = get_path(line, it + 2);
  else if (line[it] == 'W' && line[it + 1] == 'E')
    file->params->we = get_path(line, it + 2);
  else if (line[it] == 'E' && line[it + 1] == 'A')
    file->params->ea = get_path(line, it + 2);
  else if (line[it] == 'S' && line[it + 1] == ' ')
    file->params->sprt = get_path(line, it + 1);
  else if (line[it] == 'F')
    file->params->floor_rgb = get_color(line, it + 1);
  else if (line[it] == 'C')
    file->params->ceiling_rgb = get_color(line, it + 1);
  else if (line[it] == '1')
    {
      all_parameters(file->params);
      read_map(line, fd, len, file->map);
    }
  free(line);
}

void	init_values(t_file *file)
{
  file->map->map_line = 0;
  file->map->map_line = 0;
  file->map->num_sprites= 0;
  file->params->resolution_x = 0;
  file->params->resolution_y = 0;
  file->params->no = 0;
  file->params->so = 0;
  file->params->ea = 0;
  file->params->we = 0;
  file->params->sprt = 0;
}
