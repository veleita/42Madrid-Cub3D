#include "cub3D.h"

static int	rgb_to_hex(t_color color)
{
	int	ret;

	ret = color.r;
	ret = (ret << 8) | color.g;
	ret = (ret << 8) | color.b;
	return (ret);
}

void		get_texture_x(t_ray *ray)
{
	ray->texture_x = (int)(ray->wall_hit_x * (double)(ray->texture->width));
	if (ray->texture_x < 0)
		ray->texture_x = ray->texture->width - ray->texture_x - 1;
}

void		print_column(int x, t_ray *ray, t_parameters *params,
		t_images *images)
{
	int		y;
	double	texture_y;
	double	step;
	double	texture_pos;

	y = -1;
	while (++y < ray->draw_start)
		images->screen->addr[y * params->resolution_x + x] = 
			rgb_to_hex(params->ceiling_rgb);
	step = 1.0 * ray->texture->height / ray->wall_height;
	texture_pos = (ray->draw_start - params->resolution_y / 2 +
			ray->wall_height / 2) * step;
	while (y < ray->draw_end - 1)
	{
		texture_y = (int)texture_pos & (ray->texture->height - 1);
		texture_pos += step;
		images->screen->addr[y * params->resolution_x + x] = 
			ray->texture->addr[(int)(texture_y * ray->texture->width
			    + ray->texture_x)];
		y++;
	}
	while (y < (params->resolution_y - 1))
		images->screen->addr[y++ * params->resolution_x + x] = 
			rgb_to_hex(params->floor_rgb);
}
