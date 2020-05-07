#include "cub3D.h"

/*
** - Allocate memory for the var struct
** - Connect to the graphical server
** - Open a new window
** - Create a new image
** - Sets the address of the image (which is an int array) so we can
**   write on it to edit the image, which is empty for now (bzero)
** - Fill the var->file struct with the info in the fd
*/
void init(char *file_name)
{
  t_var *var;
  
  if (!(var = (t_var*)malloc(sizeof(t_var))))
    ft_exit ("Failed to allocate memory for the var struct (init.c)");
  if (!(var->mlx = mlx_init()))
    {
      free(var);
      ft_exit ("Failed to establish connection with mlx (init.c)");
    }
  if (!(var->win = mlx_new_window(var->mlx, var->file.resolution_x,
				  var->file.resolution_y, "cub3D")))
    {
      free(var);
      ft_exit ("Failed to open new window (init.c)");
    }
  if (!(var->img.id = mlx_new_image(var->mlx, var->file.resolution_x,
				    var->file.resolution_y)))
    {
      free(var);
      ft_exit ("Failed to create image (init.c)");
  var->img.addr = (int*)mlx_get_data_addr(var->img.id, &var->img.bpp,
					  &var->img.size_line,
					  &var->img.endian);
  ft_bzero(var->img.addr,
	   var->file.resolution_x * var->file.resolution_y);
  var->file = read_file(file_name);
}
