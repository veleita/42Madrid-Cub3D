#include "cub3D.h"

t_file	*read_file(const char *file_name)
{
	t_file *file;
	char	*line;
	int	len;
	int	fd;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		ft_exit("Invalid file (read_file.c)");
	if (!(file = (t_file*)malloc(sizeof(t_file))))
		ft_exit("Couldn't allocate memory for file struct (read_file.c)");
	if (!(file->map = (t_map*)malloc(sizeof(t_map))))
		ft_exit("Couldn't allocate memory for map struct (read_file.c)");
	if (!(file->params = (t_parameters*)malloc(sizeof(t_parameters))))
		ft_exit("Couldn't allocate memory for map struct (read_file.c)");
	file->map->file_name = file_name;
	init_values(file);
	while ((len = get_next_line(fd, &line)) > 0 && ++file->map->map_line)
		parse_parameters(line, len, fd, file);
	free(line);
	return (file);
}

static t_texture	*create_texture(void *mlx, char *path)
{
	t_texture *texture;

	if (!(texture = (t_texture*)malloc(sizeof(t_texture))))
		ft_exit("Couldn't allocate memory for t_texture (init.c)");
	texture->id = mlx_xpm_file_to_image(mlx, path, 
			&texture->width, &texture->height);
	texture->addr = (int*)mlx_get_data_addr(texture->id, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (texture);
}

static t_images	*create_images(void *mlx, t_parameters *params)
{
	t_images *images;

	if (!(images = (t_images*)malloc(sizeof(t_images))))
		ft_exit("Failed to allocate memory for the images struct(init.c)");
	if (!(images->screen = (t_screen*)malloc(sizeof(t_screen))))
		ft_exit("Failed to allocate memory for t_screen struct(init.c)");
	if (!(images->screen->id = mlx_new_image(mlx, params->resolution_x,
					params->resolution_y)))
		ft_exit ("Failed to create image (init.c)");
	images->screen->addr = (int*)mlx_get_data_addr(images->screen->id,
			&images->screen->bpp,
			&images->screen->size_line,
			&images->screen->endian);
	ft_bzero(images->screen->addr,
			(params->resolution_x * params->resolution_y));
	images->north = create_texture(mlx, params->no);
	images->south = create_texture(mlx, params->so);
	images->east = create_texture(mlx, params->ea);
	images->west = create_texture(mlx, params->we);
	return (images);
}

/*
 ** L:
 **
 ** L: Fill the var->file struct with the info in the fd
 */
void	init(const char *file_name, t_var *var)
{
	var->file = read_file(file_name);
	if (!(var->id = (t_id*)malloc(sizeof(t_id))))
		ft_exit ("Failed to allocate memory for t_id (init.c)");
	if (!(var->id->mlx = mlx_init()))
		ft_exit ("Failed to establish connection with mlx (init.c)");
	if (!(var->id->win = mlx_new_window(var->id->mlx,
					var->file->params->resolution_x,
					var->file->params->resolution_y,
					"cub3D")))
		ft_exit ("Failed to open new window (init.c)");
	if (!(var->ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_exit("Couldn't allocate memory for ray struct");
	var->images = create_images(var->id->mlx, var->file->params);
	if (!(var->key = (t_key*)malloc(sizeof(t_key))))
		ft_exit ("Oops error allocating t_key (init.c)");
	var->key->a = 0;
	var->key->w = 0;
	var->key->s = 0;
	var->key->d = 0;
	var->key->left = 0;
	var->key->right = 0;
}
