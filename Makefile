NAME		= cub3D

CC		= gcc
GDB		= -g
WFLAGS		= -Werror -Wall -Wextra

INCLUDES	= -I includes/

OS		= $(shell uname)
ifeq ($(OS), Linux)
	MINILIBX_DIR	= minilibx-linux/
	IFLAGS		= -L minilibx-linux -l mlx -l m -l bsd -l X11 -l Xext
endif
ifeq ($(OS), Darwin)
	MINILIBX_DIR	= minilibx_opengl/
	IFLAGS		= -L minilibx_opengl -l mlx -framework OpenGL -framework Appkit
endif

HEADERS		=	cub3D.h

SRC_DIR		=	src/
SRC		= 	main.c \
			init.c \
			read_file.c \
			read_map.c \
			parse_map.c \
			parse_utils.c \
			render.c \
			raycasting.c \
			textures.c \
			input.c \
			movement.c \
			sprites.c \
			bmp.c \
			exit.c \
			free.c \
			get_next_line.c \
			gnl_utils.c \
			utils.c \

BONUS	=	up_down.c \

OBJ_DIR		= objs/
OBJ_FILES	= $(SRC:.c=.o) $(BONUS:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all:		$(OBJ_DIR) $(NAME)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)
		@echo obj/ has been created!

$(NAME):	$(OBJS)
		@make -C $(MINILIBX_DIR)
		@$(CC) $(OBJS) $(IFLAGS) -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		@$(CC) $(GDB) $(INCLUDES) -c $< -o $@

clean:
		@rm -rf $(OBJ_DIR)
		@make -C $(MINILIBX_DIR) clean

fclean:		clean 
		@rm -rf $(NAME)
		@rm -rf $(NAME).bmp
		@echo Objects and executable file erased, bye!

re: fclean all
