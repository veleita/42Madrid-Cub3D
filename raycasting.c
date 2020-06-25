#include "cub3D.h"

/*
 ** L23: ray->camera_x is a value in the range (-1, 1)
 **	Negative numbers correspond to the left side of the map,
 **	positive numbers correspond to the right side of the map,
 **	the 0 value corresponds to the center of the map.
 **
 ** L24: ray->dir_x/y is the vectorial addition of the view direction
 **	of the player (camera->dir_x/y) and the plane of the player,
 **	a perpendicular vector scaled by the ray->camera_x value.
 **
 ** L26: ray->delta_dist_x/y is the distance travelled by the ray for
 **	each column (delta_dist_x) or line (delta_dist_y) of the map
 **
 ** L31: ray->side_dist_x/y is the distance that the ray needs to travel
 **	from the player to the first cell edge it encounters
 */
void	get_side_dist(int x, double resolution_x, t_ray *ray,
		t_camera *camera)
{
	ray->camera_x = (2 * x / (double)resolution_x) - 1;
	ray->dir_x = camera->dir_x + (camera->plane_x * ray->camera_x);
	ray->dir_y = camera->dir_y + (camera->plane_y * ray->camera_x);
	ray->map_x = (int)camera->pos_x;
	ray->map_y = (int)camera->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
		ray->side_dist_x = (camera->pos_x - ray->map_x) *
			ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - camera->pos_x) *
			ray->delta_dist_x;
	if (ray->dir_y < 0)
		ray->side_dist_y = (camera->pos_y - ray->map_y) *
			ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - camera->pos_y) *
			ray->delta_dist_y;
}

/*
 ** L: the ray->step_x/y value determines wether if the ray advances
 **	forward (1) or backwards (-1)
 **
 ** L: ray->hit is a flag which is activated when a wall (the edge of
 **	a cell with a ’1’ value on the map[][] array) is encountered
 **      by the ray
 **
 ** L: we check if the nearest cell edge is vertical (side_dist_x < )
 **	or horizontal (side_dist_y < )
 **
 ** L: note that the side_dist_x/y values are not accurate, this isn’t
 **	important, as the distance to the wall will be computed using
 **	only the pos, dir, map and step values. We only need the
 **	side_dist_x and side_dist_y values to be proportional to each
 **	other, so we can properly perform the comparison on L67
 **
 ** L: ray->side is a flag that indicates wether if the edge cell we
 **	are evaluating certical (0) or horizontal (1);
 */
void	get_hit(t_ray *ray, int **map, int map_max_x, int map_max_y)
{
	ray->step_x = (ray->dir_x < 0) ? -1 : 1;
	ray->step_y = (ray->dir_y < 0) ? -1 : 1;
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		ray->map_y = (ray->map_y >= map_max_y) ? map_max_y : ray->map_y;
		if (map[ray->map_y][ray->map_x] == 1)
			ray->hit = 1;
	}
}

/*
 ** L: ray->wall_hit_x is ???
 **
 ** L: we select the correspondent texture according to the
 **	orientation of the wall
 */
void	get_wall(t_ray *ray, t_camera *camera,
		t_parameters *params, t_texture *texture)
{
	if (ray->side == 1)
	{
		ray->wall_hit_x = camera->pos_x + ((ray->map_y - camera->pos_y
					+ (1 - ray->step_y) / 2) 
				/ ray->dir_y) * ray->dir_x;
		texture->path = (ray->dir_y < 0) ? params->so : params->no;
	}
	else
	{
		ray->wall_hit_x = camera->pos_y + ((ray->map_x - camera->pos_x
					+ (1 - ray->step_x) / 2)
				/ ray->dir_x) * ray->dir_y;
		texture->path = (ray->dir_x < 0) ? params->ea : params->we;
	}
	ray->wall_hit_x -= floor(ray->wall_hit_x);
	/*   printf("%s\n", texture->path); */
}

/*
 ** L119: perp_wall_dist is the perpendicular distance from the player
 **	 to the wall
 **
 ** L127: the perp_wall_dist value is a scalar, not a vector, it must
 **	 always be a positive number.
 */
void	get_wall_dist(t_ray *ray, t_camera *camera)
{
	if (ray->side == 1)
		ray->perp_wall_dist = fabs((ray->map_y - camera->pos_y +
				(1 - ray->step_y) / 2.0) / ray->dir_y);
	else
		ray->perp_wall_dist = fabs((ray->map_x - camera->pos_x +
				(1 - ray->step_x) / 2.0) / ray->dir_x);
	ray->perp_wall_dist *= (ray->perp_wall_dist < 0) ? -1 : 1;
}

/*
 ** L136: the wall height is inversely proportional to its distance
 */
void	get_wall_height(t_ray *ray, t_parameters *parameters)
{
	ray->wall_height = (int)(parameters->resolution_y /
			ray->perp_wall_dist);
	ray->draw_start = (parameters->resolution_y / 2) -
		(ray->wall_height / 2);
	ray->draw_start = (ray->draw_start < 0) ? 0 : ray->draw_start;
	ray->draw_end = (parameters->resolution_y / 2) +
		(ray->wall_height / 2);
	ray->draw_end = (ray->draw_end > parameters->resolution_y) ?
		parameters->resolution_y : ray->draw_end;
} 
