#include "cub3D.h"

int main(int argc, char **argv)
{
  t_file *file;
  int i = 0;
  int j;
  
  file = read_file(argv[1]);
  
  printf("Resolution x %d\nResolution y %d\n\n",
	 file->parameters->resolution_x, file->parameters->resolution_y);

  printf("no %s\nso %s\nea %s\nwe %s\n\n",
	 file->parameters->no, file->parameters->so,
	 file->parameters->ea, file->parameters->we);

  printf("sprt %s\n\n", file->parameters->sprt);

  printf("Floor %d %d %d\nCeiling %d %d %d\n\n",
	 file->parameters->floor_rgb.r, file->parameters->floor_rgb.g,
	 file->parameters->floor_rgb.b, file->parameters->ceiling_rgb.r,
	 file->parameters->ceiling_rgb.g,
	 file->parameters->ceiling_rgb.b);

  printf("Pos x = %f\nPos y = %f\nDir x = %f\nDir y = %f\nPlane x = %f\nPlane y = %f\n\n",
	 file->map->camera->pos_x, file->map->camera->pos_y,
	 file->map->camera->dir_x, file->map->camera->dir_y,
	 file->map->camera->plane_x, file->map->camera->plane_y);
  
  while (i < (file->map->y))
    {
      j = 0;
      while (j < file->map->x)
	{
	  printf("%d", file->map->map[i][j]);
	  j++;
	}
      printf("\n");
      i++;
    }
 /*
  char *line;
  int fd = open(argv[1], O_RDONLY);
  while (get_next_line(fd, &line) > 0)
    printf("%s\n", line);
 */
  return (0);
}
