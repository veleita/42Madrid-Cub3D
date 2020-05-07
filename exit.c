#include "cub3D.h"

void ft_exit(char *error)
{
  // I may need to free the allocated memory before the exit
  write(1, error, ft_strlen(error));
  write(1, "\n", 1);
  exit(1);
}
