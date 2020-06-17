/*
** |------HEADERS------|
/* 
** For the mlx functions: 
*/
#include <mlx.h>
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
** For the printf function (debugging and testing purposes):
*/
#include <stdio.h>

/*
** |------STRUCTS------| 
*/
typedef struct	s_camera
{
  double	pos_x;
  double	pos_y;
  double	dir_x;
  double	dir_y;
  double	plane_x;
  double	plane_y;
}		t_camera;

typedef struct	s_map
{
  const char	*file_name;
  int		map_line;
  int		x;
  int		y;
  t_camera	*camera;
  int		**map;
}		t_map;

/*
** The rgb values in the s_color struct are integers from 0 to 255 
*/
typedef struct	s_color
{
  unsigned char	r;
  unsigned char	g;
  unsigned char	b;
}		t_color;

typedef struct	s_parameters
{
  int		resolution_x;
  int		resolution_y;
  char		*no;
  char		*so;
  char		*ea;
  char		*we;
  char		*sprt;
  t_color 	floor_rgb;
  t_color	ceiling_rgb;
}		t_parameters;
  
typedef struct	s_file
{
  t_parameters	*parameters;
  t_map		*map;
}		t_file;

typedef struct	s_img
{
  void		*id;
  int		*addr;
  int		endian;
  int		bpp;
  int		size_line;
}		t_img;

typedef struct	s_texture
{
  void		*id;
  int		width;
  int		height;
  int		*addr;
  int		endian;
  int		bpp;
  int		size_line;
  char		*path;
}		t_texture;

typedef struct	s_ray
{
  double	camera_x;
  double	dir_x;
  double	dir_y;
  int		map_x;
  int		map_y;
  double	delta_dist_x;
  double	delta_dist_y;
  double	side_dist_x;
  double	side_dist_y;
  int		step_x;
  int		step_y;
  short		hit;
  short		side;
  double	perp_wall_dist;
  double	wall_hit_x;
  // Not sure if the three following should be int or double values
  int		wall_height;
  int		draw_start;
  int		draw_end;
}		t_ray;

# define A_KEY 0
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define ESC_KEY 53

/*
** All the following unsigned chars are meant to be boolean values (0 or 1)
*/
typedef struct	s_key
{
  unsigned char	a;
  unsigned char	w;
  unsigned char	s;
  unsigned char	d;
  unsigned char	left;
  unsigned char	right;
}		t_key;

typedef struct	s_var //this struct is probably unnecesary
{
  void		*mlx;
  void		*win;
  t_file	*file;
  t_img		*img;
  t_texture	*texture;
  t_ray		*ray;
  t_key		*key;
}		t_var;

/*
** |------FUNCTIONS------| 
** 
** init.c 
*/
void		init(const char *file_name);
t_file		*read_file(const char *file_name);
/* 
** read_file.c 
*/
void		init_values(t_file *file);
void		parse_parameters(char *line, int len, int fd, t_file *file);
/* 
** read_map.c 
*/
void		read_map(char *line, int fd, int len, t_map *map);
/* 
** parse_map.c 
*/
void		all_parameters(t_parameters *parameters);
void		get_map_dimensions(char *line, int fd, short read,
				   t_map *map);
t_camera	*check_coord(char coord, int pos_x, int pos_y);
/*
** valid_map.c
*/
void		 valid_map(t_map *map, int y, int x);
/* 
** render.c
*/
void		render(t_parameters *parameters, t_camera *camera,
		       int **map, t_texture *texture);
/*
** raycasting.c
*/
void		get_side_dist(int x, double resolution_x, t_ray *ray,
			      t_camera *camera);
void		get_hit(t_ray *ray, int **map);
void		get_wall(t_ray *ray, t_camera *camera,
			 t_parameters *parameters, t_texture *texture);
void		get_wall_dist(t_ray *ray, t_camera *camera);
void		get_wall_height(t_ray *ray, t_parameters *parameters);
/* 
** exit.c 
*/
void		ft_exit(char *error);
/*
** get_next_line.c
*/
short		get_next_line(int fd, char **line);
/*
** gnl_utils.c
*/
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
short		ft_strchr(char *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
/* 
** utils.c 
*/
void		remove_space(char *line, int *it);// used
size_t		ft_strlen(const char *s);// used
void		ft_bzero(void *s, size_t n);// used
short		ft_isdigit(int c);// used
short		ft_isalpha(int c);// used
//char		*ft_strnstr(const char *haystack, const char *needle,
//			    size_t len);//
//short		ft_strcmp(const char *s1, const char *s2);//
/*
void		fill_map(char *line, int **map, int x);
int		**create_map(char *file_name, int x, int y);
/* /* render.c 
*void		render(t_var *var);//here
* raycasting.c
*void		get_side_dist(int x, t_var *var);// here
*
*void		get_hit(t_var *var);// here
*void		get_wall(t_var *var);// here
*void		get_wall_hit(t_var *var);// here
** print_world.c
*void		print_column(t_var *var, int x, int texture_x);// here
*char		*select_texture(t_var *var);// here
*/
/*
void		*ft_memcpy(void *dst, const void *src, size_t n);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchr(char *s, char c);
int		get_next_line(int fd, char **line);// used
/* movement.c
void		vertical_movement(t_var *var, double movement_speed,
				  double dirX, double dirY);
void		horizontal_movement(t_var *var, double movement_speed,
				    double planeX, double planeY);
void		rotation(t_var *var, double rotation_speed);
/* keys.c
short		key_pressed(int key_code, t_var *var);// here
short		key_released(int key_code, t_var *var);// here
int		move_player(t_var *var);// what did this do????
*/
