#include "cub3D.h"

t_texture *create_texture(void)
{
  t_texture *texture;
  
  if (!(texture = (t_texture*)malloc(sizeof(t_texture))))
    ft_exit("Couldn't allocate memory for t_texture (textures.c)");
  return (texture);
}

void get_texture_address(t_var *var)
{
  var->texture->id = mlx_xpm_file_to_image(var->mlx, var->texture->path,
				      &var->texture->width, &var->texture->height);
  var->texture->addr = (int*)mlx_get_data_addr(var->texture->id, &var->texture->bpp,
					  &var->texture->size_line,
					  &var->texture->endian);
}
