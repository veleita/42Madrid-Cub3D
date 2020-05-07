#include "cub3D.h"

int main(int argc, char **argv)
{
  t_var *var;
  int i = 0;
  int j = 0;
  
  /* Allocate memory for the var struct */
  if (!(var = (t_var*)malloc(sizeof(t_var))))
    ft_exit ("Failed to allocate memory for the var struct");
  var->file = init_file(argv[1]);
  while (j < (var->file->map->y - 1))
    {
      i = 0;
      while (i < 25)
	{
	  printf("%d", var->file->map->map[i][j]);
	  i++;
	}
      printf("\n");
      j++;
    }
 /*
  char *line;
  int fd = open(argv[1], O_RDONLY);
  while (get_next_line(fd, &line) > 0)
    printf("%s\n", line);
 */
  return (0);
}
