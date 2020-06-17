NAME		= cub3D

CC		= gcc

OS		= $(shell uname)
ifeq ($(OS), Linux)
	IFLAGS	= -L minilibx-linux -l mlx -l m -l bsd -l X11 -l Xext
endif
#ifeq ($(OS), Darwin)
#	IFLAGS	= -L minilib_mac -l mlx -framework OpenGL -framework Appkit
#endif
WFLAGS		= -Werror -Wall -Wextra
GDB		= -g

HEADER		=	cub3D.h

SRC		= 	main.c \
			init.c \
			read_file.c \
			read_map.c \
			parse_map.c \
			valid_map.c \
			render.c \
			raycasting.c \
			exit.c \
			get_next_line.c \
			gnl_utils.c \
			utils.c \

PARSE_SRC	=	test_main.c \
			init.c \
			read_file.c \
			read_map.c \
			parse_map.c \
			valid_map.c \
			exit.c \
			get_next_line.c \
			gnl_utils.c \
			utils.c \

all:	$(NAME)
	./$(NAME) maps/map1.cub

$(NAME): $(SRC) $(HEADER)
	$(CC) $(IFLAGS) $(SRC) -o $(NAME)

# TEST THE PARSE FUNCTIONS
parse:	$(PARSE_SRC) $(HEADER)
	$(CC) $(GDB) $(PARSE_SRC) && ./a.out maps/map1.cub
	rm a.out
