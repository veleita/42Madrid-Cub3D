#include "cub3D.h"

t_file	*read_file(const char *file_name)
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
  if (!(file->parameters = (t_parameters*)malloc(sizeof(t_parameters))))
    ft_exit("Couldn't allocate memory for map struct (read_file.c)");
  file->map->file_name = file_name;
  init_values(file);
  while ((len = get_next_line(fd, &line)) > 0 && ++file->map->map_line)
    parse_parameters(line, len, fd, file);
  free(line);
  return (file);
}

/*
** L: Sets the address of the image (which is an int array) so we can
** 	write on it to edit the image, which is empty for now (bzero)
**
** L: Fill the var->file struct with the info in the fd
*/
void	init(const char *file_name)
{
  t_var *var;
  
  if (!(var = (t_var*)malloc(sizeof(t_var))))
    ft_exit ("Failed to allocate memory for the var struct (init.c)");
/*   if (!(var->mlx = mlx_init())) */
/*     ft_exit ("Failed to establish connection with mlx (init.c)"); */
/*   if (!(var->win = mlx_new_window(var->mlx, var->file.resolution_x, */
/* 				  var->file.resolution_y, "cub3D"))) */
/*       ft_exit ("Failed to open new window (init.c)"); */
/*   if (!(var->img.id = mlx_new_image(var->mlx, var->file.resolution_x, */
/* 				    var->file.resolution_y))) */
/*       ft_exit ("Failed to create image (init.c)"); */
/*   var->img.addr = (int*)mlx_get_data_addr(var->img.id, &var->img.bpp, */
/* 					  &var->img.size_line, */
/* 					  &var->img.endian); */
/*   ft_bzero(var->img.addr, */
/* 	   var->file.resolution_x * var->file.resolution_y); */
  var->file = read_file(file_name);
/*   var->texture = create_texture(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/*   render(var->file->parameters, var->file->map->camera, */
/* 	 var->file->map->map, var->texture); */
}
