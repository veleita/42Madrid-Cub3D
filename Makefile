# NAME		= cub3D

CC		= gcc
# WFLAGS	= -Werror -Wall -Wextra
GDB		= -g

# INCLUDES	= -l mlx 0I /usr/X11/include
# FRAMEWORKS	= -framework Appkit -framework OpenGL

# SRC		= 	main.c \
# 			init.c \
# 			read_file.c \
# 			read_map.c \
# 			parse_map.c \
# 			utils.c \
# 			exit.c \

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

# all:	$(NAME)
# 	./$(NAME) maps/map1.cub

# TEST THE PARSE FUNCTIONS

parse:	$(PARSE_SRC) cub3D.h
	$(CC) $(GDB) $(PARSE_SRC) && ./a.out maps/map1.cub
#	rm a.out
