/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzomeno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:44:35 by mzomeno-          #+#    #+#             */
/*   Updated: 2020/07/15 21:08:38 by mzomeno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define	CUB3D_H
#endif

#include "mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct		s_camera
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_camera;

typedef struct		s_sprite
{
	double			pos_x;
	double			pos_y;
}					t_sprite;

typedef struct		s_map
{
	const char		*file_name;
	int				map_line;
	int				x;
	int				y;
	t_camera		*camera;
	int				num_sprites;
	t_sprite		**sprite;
	int				**map;
}					t_map;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct		s_parameters
{
	int				resolution_x;
	int				resolution_y;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	char			*sprt;
	t_color			floor_rgb;
	t_color			ceiling_rgb;
}					t_parameters;

typedef struct		s_file
{
	t_parameters	*params;
	t_map			*map;
}					t_file;

typedef struct		s_screen
{
	void			*id;
	int				*addr;
	int				endian;
	int				bpp;
	int				size_line;
}					t_screen;

typedef struct		s_texture
{
	void			*id;
	int				width;
	int				height;
	int				*addr;
	int				endian;
	int				bpp;
	int				size_line;
}					t_texture;

typedef struct		s_images
{
	t_screen		*screen;
	t_texture		*north;
	t_texture		*south;
	t_texture		*east;
	t_texture		*west;
	t_texture		*sprite;
}					t_images;

typedef struct		s_sprite_ray
{
	double			inv_det;
	int				*sprite_order;
	double			sprite_x;
	double			sprite_y;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	double			*wall_z;
	int				tex_x;
	int				tex_y;
}					t_sprite_ray;

typedef struct		s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	short			hit;
	short			side;
	double			perp_wall_dist;
	double			wall_hit_x;
	t_texture		*texture;
	int				texture_x;
	double			wall_height;
	double			draw_start;
	double			draw_end;
}					t_ray;

#ifdef __APPLE__
# define A_KEY 0
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define ESC_KEY 53
# define X_BTN 17

#elif defined __unix__
# define A_KEY 97
# define W_KEY 119
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC_KEY 65307
# define X_BTN 33
#endif

typedef struct		s_key
{
	unsigned char	a;
	unsigned char	w;
	unsigned char	s;
	unsigned char	d;
	unsigned char	left;
	unsigned char	right;
	unsigned char	esc;
}					t_key;

typedef struct		s_id
{
	void			*mlx;
	void			*win;
}					t_id;

typedef struct		s_var
{
	t_id			*id;
	t_file			*file;
	t_images		*images;
	t_key			*key;
	double			mov_speed;
	double			rotate_speed;
	t_ray			*ray;
	t_sprite_ray	*spr_ray;
}					t_var;

void				init(const char *file_name, t_var *var);
void				init_values_render(t_var *var);
t_file				*read_file(const char *file_name);
void				init_values_file(t_file *file);
void				parse_parameters(char *line, int len, int fd,
					t_file *file);
void				get_resolution(char *line, t_parameters *params, int it);
char				*get_path(char *line, int it);
t_color				get_color(char *line, int it);
void				read_map(char *line, int fd, int len, t_map *map);
void				all_parameters(t_parameters *parameters);
int					get_map_dimensions(char *line, int fd, short read,
					t_map *map);
t_camera			*check_coord(char coord, int pos_x, int pos_y);
void				valid_map(t_map *map, int y, int x);
void				render(t_file *file, t_ray *ray, t_images *images,
					t_sprite_ray *s_ray);
int					actualize(t_var *var);
void				get_side_dist(int x, double resolution_x, t_ray *ray,
					t_camera *camera);
void				get_hit(t_ray *ray, int **map, int map_max_y);
void				get_wall(t_ray *ray, t_camera *camera,
					t_images *images);
void				get_wall_dist(t_ray *ray, t_camera *camera,
					t_sprite_ray *s_ray, int x);
void				get_wall_height(t_ray *ray, t_parameters *parameters);
void				get_texture_x(t_ray *ray);
void				print_column(int x, t_ray *ray, t_parameters *params,
					t_images *images);
int					key_pressed(int keycode, t_key *key);
int					key_released(int keycode, t_key *key);
void				rotation(t_camera *camera, double rotation_speed);
void				horizontal_movement(t_map *map, double movement_speed,
					double plane_x, double plane_y);
void				vertical_movement(t_map *map, double movement_speed,
					double dir_x, double dir_y);
void				order_sprites(int *num_sprites, t_map *map);
void				render_sprites(t_var *var);
void				create_bmp(t_parameters *params, int *screen);
t_var				*get_var(void);
void				ft_exit_fail(char *error);
int					ft_exit_success(t_var *var);
void				free_all(t_var *var);
void				free_spr_ray(t_sprite_ray *spr_ray);
void				free_images(t_images *images);
void				destroy_images(t_images *images, void *mlx);
void				free_file(t_file *file);
void				free_map(t_map *map);
short				get_next_line(int fd, char **line);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
short				ft_strchr(char *s, char c);
char				*ft_substr(char const *s, unsigned int start,
					size_t len);
void				remove_space(char *line, int *it);
void				ft_bzero(void *s, size_t n);
short				ft_isalpha(int c);
void				bubble_sort(int *list, double *content, int elements);
int					ft_strcmp(const char *s1, const char *s2);
