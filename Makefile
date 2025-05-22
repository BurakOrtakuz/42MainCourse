NAME			=	cub3D
NAME_BONUS		=	cub3D_bonus
CC				=	gcc
FLAGS			=	-Wall -Wextra -Werror
SRC				=	./src/checker/check_arg.c \
					./src/checker/check_inside_map.c \
					./src/checker/check_map.c \
					./src/checker/check_outside_map.c \
					./src/checker/check_values.c \
					./src/checker/set_img.c \
					./src/checker/set_map.c \
					./src/checker/set_mini_map.c \
					./src/checker/set_mini_map2.c \
					./src/checker/set_values.c \
					./src/error/error_message.c \
					./src/error/free_program.c \
					./src/error/free_tmap.c \
					./src/error/handle_error.c \
					./src/key/key_down.c \
					./src/key/key_events.c \
					./src/main/init_program.c \
					./src/main/move.c \
					./src/main/put_pixel.c \
					./src/raycasting/all_rays.c \
					./src/raycasting/raycasting_utils.c \
					./src/raycasting/raycasting.c \
					./src/raycasting/raycasting_line.c \
					./src/utils/map_checker_utils1.c \
					./src/utils/map_checker_utils2.c \
					./src/utils/value_checker_utils1.c \
					./src/utils/value_checker_utils2.c

MAIN			=	./src/main/main.c \
					./src/main/render.c \

MAIN_BONUS		=	./src/bonus/main_bonus.c \
					./src/bonus/bonus_map.c \
					./src/bonus/render_bonus.c

OBJ				=	$(SRC:.c=.o)
OBJ_MAIN		=	$(MAIN:.c=.o)
OBJ_BONUS		=	$(MAIN_BONUS:.c=.o)

MINILIBX_PATH	=	./minilibx
LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

all:    			mlx $(LIBFT) $(NAME)
bonus:				mlx $(LIBFT) $(NAME_BONUS)

$(NAME):			$(OBJ) $(OBJ_MAIN)
					$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(OBJ_MAIN) -framework OpenGL -framework AppKit -L$(MINILIBX_PATH) -lmlx

$(NAME_BONUS):		$(OBJ) $(OBJ_BONUS)
					$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJ) $(LIBFT) $(OBJ_BONUS) -framework OpenGL -framework AppKit -L$(MINILIBX_PATH) -lmlx
$(LIBFT):
					@make -C $(LIBFT_PATH) all
mlx:
					@make -C $(MINILIBX_PATH) all

exe:				$(NAME)
					./so_long
clean:
					@rm -rf $(OBJ)
					@rm -rf $(OBJ_MAIN)
					@rm -rf $(OBJ_BONUS)
					@make -C $(LIBFT_PATH) clean
					@make -C $(MINILIBX_PATH) clean

fclean:				clean
					@rm -rf $(NAME)
					@rm -rf $(NAME_BONUS)
					@make -C $(LIBFT_PATH) fclean

re:					fclean all
.PHONY:				all clean fclean re libft bonus
