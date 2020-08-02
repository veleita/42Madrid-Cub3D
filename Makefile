NAME		= cub3D
NAME_BONUS	= cub3D_bonus

MAP			= minecraft.cub
CC		= gcc
GDB		= -g
WFLAGS		= -Werror -Wall -Wextra

INCLUDES	= -I includes/

OS		= $(shell uname)
ifeq ($(OS), Linux)
	MINILIBX_DIR	= minilibx-linux-master/
	IFLAGS		= -L minilibx-linux-master -l mlx -l m -l bsd -l X11 -l Xext
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

SRC_BONUS_DIR		=	src_bonus/

SRC_BONUS		= 	main.c \
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
			up_down.c \

OBJ_DIR		= objs/
OBJ_FILES	= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

OBJ_BONUS_DIR		= objs_bonus/
OBJ_FILES_BONUS	= $(SRC_BONUS:.c=.o)
OBJS_BONUS		= $(addprefix $(OBJ_BONUS_DIR), $(OBJ_FILES_BONUS))

all:		$(OBJ_DIR) $(NAME)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)
		@echo obj/ has been created!

$(NAME):	$(OBJS)
		@make -C $(MINILIBX_DIR) &> output.txt
		@rm output.txt
		@echo minilibx has been compiled!
		@$(CC) $(OBJS) $(IFLAGS) -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		@$(CC) $(GDB) $(INCLUDES) -c $< -o $@

bonus:		$(OBJ_BONUS_DIR) $(NAME_BONUS)

$(OBJ_BONUS_DIR):
		@mkdir $(OBJ_BONUS_DIR)
		@echo obj/ has been created!

$(NAME_BONUS):	$(OBJS_BONUS)
		@make -C $(MINILIBX_DIR) &> output.txt
		@rm output.txt
		@echo minilibx has been compiled!
		@$(CC) $(OBJS_BONUS) $(IFLAGS) -o $(NAME_BONUS)

$(OBJ_BONUS_DIR)%.o:	$(SRC_BONUS_DIR)%.c
		@$(CC) $(GDB) $(INCLUDES) -c $< -o $@

run:	bonus
		@./$(NAME_BONUS) maps/$(MAP) &> output.txt
		@rm output.txt
clean:
		@make -C $(MINILIBX_DIR) clean &> output.txt
		@echo cleaned minilibx!
		@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR) output.txt
		@echo cleaned objects!

fclean:		clean 
		@rm -rf $(NAME) $(NAME_BONUS) $(NAME).bmp
		@echo executable file erased, bye!

re: fclean all
