#include "cub3D.h"

int main(int argc, char **argv)
{
  t_file *file;
  int i = 0;
  int j;
  
  file = init_file(argv[1]);
  
  printf("Resolution x %d\nResolution y %d\n\n",
	 file->resolution_x, file->resolution_y);

  printf("no %s\nso %s\nea %s\nwe %s\n\n",
	 file->no, file->so, file->ea, file->we);

  printf("sprt %s\n\n", file->sprt);

  printf("no %s\nso %s\nea %s\nwe %s\n\n",
	 file->no, file->so, file->ea, file->we);

  printf("Floor %d %d %d\nCeiling %d %d %d\n\n",
	 file->floor_rgb.r, file->floor_rgb.g, file->floor_rgb.b,
	 file->ceiling_rgb.r, file->ceiling_rgb.g, file->ceiling_rgb.b);

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
