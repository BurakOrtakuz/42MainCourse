NAME	=	so_long
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRC		=	./map_validations/map_validation.c \
			./map_validations/variables.c \
			./map_validations/error_managament.c \
			./utils/so_long_utils_extra.c \
			./utils/ft_split.c \
			./utils/ft_itoa.c \
			./utils/so_long_utils.c \
			./utils/get_next_line/get_next_line_utils.c \
			./utils/get_next_line/get_next_line.c \
			./enemy_animation_set.c \
			./enemy.c \
			./list.c \
			./animation.c \
			./set_sprite.c \
			./key_hooks.c \
			./key_events.c \
			./main.c

OBJS    =	$(SRC:.c=.o)

MLX_DIR =	./minilibx
ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -I$(MLX_DIR)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11
else
	INCLUDES = -I/opt/X11/include -I$(MLX_DIR)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

all: $(MLX_DIR)/libmlx.a $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(MLX_DIR)/libmlx.a:
	@make -C $(MLX_DIR)

clean:
	@rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re