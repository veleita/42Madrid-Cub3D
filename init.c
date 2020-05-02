#include "cub3D.h"

void init(int fd)
{
  t_var *var;
  
  /* Allocate memory for the var struct */
  if (!(var = (t_var*)malloc(sizeof(t_var))))
    ft_exit ("Failed to allocate memory for the var struct");
  /* Connect to the graphic server */
  if (!(var->mlx = mlx_init()))
    exit ("Failed to establish connection with mlx");
  /* Open a new window */
  if (!(var->win = mlx_new_window(var->mlx, var->file.resolution_x,
				  var->file.resolution_y, "cub3D")))
    exit ("Failed to open new window");
  /* Create a new image */
  if (!(var->img.id = mlx_new_image(var->mlx, var->file.resolution_x,
				    var->file.resolution_y)))
    exit ("Failed to create image");
  /* Sets the address of the image (which is an int array) so we can
   * write on it to edit the image, which is empty for now (bzero) */
  var->img.addr = (int*)mlx_get_data_addr(var->img.id, &var->img.bpp,
					  &var->img.size_line,
					  &var->img.endian);
  ft_bzero(var->img.addr,
	   var->file.resolution_x * var->file.resolution_y);
  /* Fill the var->file struct with the info in the fd */
  var->file = read_map(fd);
}
