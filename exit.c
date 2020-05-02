#include "cub3D.h"

void ft_exit(char *error)
{
  // I may need to free the allocated memory before the exit
  write(1, error, ft_strlen(error));
  exit(1);
}
