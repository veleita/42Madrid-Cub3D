#include "cub3D.h"

static void	get_resolution(char *line, t_map *file, int it)
{
  /* Check if resolution values have been already registered */
  if (file->resolution_x != 0 || file->resolution_y != 0)
    ft_exit("Found more than one resolution value");
  /* Iterates through the spaces between the identifier ’R’ and the
   * resolution values 						    */
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
  /* The minimum resolution is set to 50x50 */
  map->resolution_x = map->resolution_x < 50 ? 50 : map->resolution_x;
  map->resolution_y = map->resolution_y < 50 ? 50 : map->resolution_y;
  /* The maximum resolution is set to 2560x1440 */
  map->resolution_x = map->resolution_x > 2560 ? 2560 : map->resolution_x;
  map->resolution_y = map->resolution_y > 1440 ? 1440 : map->resolution_y;
}

static char	*get_path(int it)
{
  char *ret;
  char len;

  remove_space(line, &it);
  /* Reads everyting in the line that is not a space, len - it would be
   * the number of characters in the path */
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

static t_color	*get_color(char *line, int it)
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
  /* Check if the registered values are correct */
  if (ret.r > 255 || ret.g > 255 || ret.b > 255 ||
      ret.r < 0 || ret.g < 0 || ret.b < 0)
    ft_exit("Invalid rgb values");
  return (&ret);
}

void		parse_parameters(char **line, int len, int it,
				 t_map *file)
{
  remove_space(*line, &it);
  /* line[it] is the first character in the line after trimming
   * the spaces 						    */
  if (*line[it] == 'R')
    get_resolution(*line, file, it + 1);      
  else if (*line[it] == 'N' && *line[it + 1] == 'O')
    file->no = get_path(it);
  else if (*line[it] == 'S' && *line[it + 1] == 'O')
    file->so = get_path(it);
  else if (*line[it] == 'W' && *line[it + 1] == 'E')
    file->we = get_path(it);
  else if (*line[it] == 'E' && *line[it + 1] == 'A')
    file->ea = get_path(it);
  else if (*line[it] == 'S' && *line[it + 1] == ' ')
    file->sprt = get_path(it);
  else if (*line[it] == 'F')
    file->floor_rgb = get_color(*line, it + 1);
  else if (*line[it] == 'C')
    file->ceiling_rgb = get_color(*line, it + 1);
  else if (*line[it] == '1')
    {
      all_parameters(file);
      read_map(*line, fd, len, file->map);
    }
}

t_file		init_file(int fd, char *file_name)
{
  t_map	*file;
  char	**line;
  int	len;

  /* Allocates memory to read the file line by line */
  if (!(line = (char**)malloc(sizeof(char*))))
    ft_exit("Couldn't allocate memory for line when parsing map file");
  if (!(file = (t_map*)malloc(sizeof(t_map))))
    ft_exit("Failed to allocate memory for the map struct");
  file->map->file_name = file_name;
  /* Init values */
  file->resolution_x = 0;
  file->resolution_y = 0;
  file->no = 0;
  file->so = 0;
  file->ea = 0;
  file->we = 0;
  file->sprt = 0;
  while ((len = get_next_line(fd, line)) > 0)
      parse_parameters(line, len, 0, file);
}
