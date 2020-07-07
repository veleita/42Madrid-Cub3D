/*
 ** |------HEADERS------|
 **
 ** For the mlx functions: 
 */
#include "mlx.h"
/* 
 ** For the open function: 
 */
#include <fcntl.h>
/* 
 ** For the read and write functions:
 */
#include <unistd.h>
/* 
 ** For the exit function:
 */
#include <stdlib.h>
/*
 ** For the sqrt and cos functions:
 */
#include <math.h>
/* 
 ** For the printf function (debugging and testing purposes):
 */
#include <stdio.h>

/*
 ** |------STRUCTS------| 
 */
typedef struct		s_camera
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}			t_camera;

typedef struct		s_sprite
{
	double		pos_x;
	double		pos_y;
}			t_sprite;

typedef struct		s_map
{
	const char	*file_name;
	int		map_line;
	int		x;
	int		y;
	t_camera	*camera;
	int		num_sprites;
	t_sprite	**sprite;
	int		**map;
}			t_map;

/*
 ** The rgb values in the s_color struct are integers from 0 to 255 
 */
typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}			t_color;

typedef struct		s_parameters
{
	int		resolution_x;
	int		resolution_y;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	char		*sprt;
	t_color 	floor_rgb;
	t_color		ceiling_rgb;
}			t_parameters;

typedef struct		s_file
{
	t_parameters	*params;
	t_map		*map;
}			t_file;

typedef struct		s_screen
{
	void		*id;
	int		*addr;
	int		endian;
	int		bpp;
	int		size_line;
}			t_screen;

typedef struct		s_texture
{
	void		*id;
	int		width;
	int		height;
	int		*addr;
	int		endian;
	int		bpp;
	int		size_line;
}			t_texture;

typedef struct		s_images
{
	t_screen	*screen;
	t_texture	*north;
	t_texture	*south;
	t_texture	*east; 
	t_texture	*west;
	t_texture	*sprite;
}			t_images;

typedef struct		s_sprite_ray
{
	double		inv_det;
	int		*sprite_order;
	double		sprite_x;
	double		sprite_y;
	double		transform_x;
	double		transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	double		*wall_z;
	int		tex_x;
	int		tex_y;
}			t_sprite_ray;

typedef struct		s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int		map_x;
	int		map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int		step_x;
	int		step_y;
	short		hit;
	short		side;
	double		perp_wall_dist;
	double		wall_hit_x;
	t_texture	*texture;
	int		texture_x;
	double		wall_height;
	double		draw_start;
	double		draw_end;
}			t_ray;

#ifdef __APPLE__
# define A_KEY 0
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define ESC_KEY 53

#elif defined __unix__
# define A_KEY 97
# define W_KEY 119
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC_KEY 65307
#endif


/*
 ** All the following unsigned chars are meant to be boolean values (0 or 1)
 */
typedef struct		s_key
{
	unsigned char	a;
	unsigned char	w;
	unsigned char	s;
	unsigned char	d;
	unsigned char	left;
	unsigned char	right;
	unsigned char	esc;
}			t_key;

typedef struct		s_id
{
	void		*mlx;
	void		*win;
}			t_id;

typedef struct	s_var //this struct is probably unnecesary
{
	t_id		*id;
	t_file		*file;
	t_images	*images;
	t_key		*key;
	double		mov_speed;
	double		rotate_speed;
	t_ray		*ray;
	t_sprite_ray	*spr_ray;
}			t_var;

/*
 ** |------FUNCTIONS------| 
 ** 
 ** init.c 
 */
void			init(const char *file_name, t_var *var);
void			zero_values(t_var *var);
t_file			*read_file(const char *file_name);
/* 
 ** read_file.c 
 */
void			init_values(t_file *file);
void			parse_parameters(char *line, int len, int fd, t_file *file);
/* 
 ** read_map.c 
 */
void			read_map(char *line, int fd, int len, t_map *map);
/* 
 ** parse_map.c 
 */
void			all_parameters(t_parameters *parameters);
void			get_map_dimensions(char *line, int fd, short read,
			t_map *map);
t_camera		*check_coord(char coord, int pos_x, int pos_y);
void			valid_map(t_map *map, int y, int x);
/* 
 ** render.c
 */
void			render(t_file *file, t_ray *ray, t_images *images,
			t_sprite_ray *s_ray);
int			actualize(t_var *var);
/*
 ** raycasting.c
 */
void			get_side_dist(int x, double resolution_x, t_ray *ray,
			t_camera *camera);
void			get_hit(t_ray *ray, int **map, int map_max_y);
void			get_wall(t_ray *ray, t_camera *camera, t_images *images);
void			get_wall_dist(t_ray *ray, t_camera *camera, 
			t_sprite_ray *s_ray, int x);
void			get_wall_height(t_ray *ray, t_parameters *parameters);
/*
 ** textures.c
 */
void			get_texture_x(t_ray *ray);
void			print_column(int x, t_ray *ray, t_parameters *params,
			t_images *images);
/*
 ** input.c
 */
int			key_pressed(int keycode, t_key *key);
int			key_released(int keycode, t_key *key);
/*
 ** movement.c
 */
void			rotation(t_camera *camera, double rotation_speed);
void			horizontal_movement(t_map *map, double movement_speed,
			double plane_x, double plane_y);
void			vertical_movement(t_map *map, double movement_speed,
			double dir_x, double dir_y);
/*
** sprites.c
*/
void			order_sprites(int *num_sprites, t_map *map);
void			render_sprites(t_var *var);
/*
 * bmp.c
 */
void			create_bmp(t_parameters *params, int *screen);
/*
** exit.c 
*/
void 			ft_exit_fail(char *error);
int			ft_exit_success(t_var *var);
/*
** get_next_line.c
*/
short			get_next_line(int fd, char **line);
/*
** gnl_utils.c
*/
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
short			ft_strchr(char *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
/* 
** utils.c 
*/
void			remove_space(char *line, int *it);
void			ft_bzero(void *s, size_t n);
short			ft_isalpha(int c);
void			bubble_sort(int *list, double *content, int elements);
int			ft_strcmp(const char *s1, const char *s2);
