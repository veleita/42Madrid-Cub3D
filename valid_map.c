#include "cub3D.h"

void valid_map(t_map *map, int y, int x)
{
  if (map->map[y][x] == 0 && (x == (map->x - 1) || y == map->y ||
			      x == 0 || y == 0))
    ft_exit("Invalid map");
  map->map[y][x] = map->map[y][x] == 0 ? 3 : 1;
  if (y != (map->y - 1))
    if (map->map[y + 1][x] == 0)
      valid_map(map, y + 1, x);
  if (y != 0)
    if (map->map[y - 1][x] == 0)
      valid_map(map, y - 1, x);
  if (x != (map->x - 1))
    if (map->map[y][x + 1] == 0)
      valid_map(map, y, x + 1);
  if (x != 0)
    if (map->map[y][x - 1] == 0)
      valid_map(map, y, x - 1);
}
