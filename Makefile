NAME    =   philo
CC      =   gcc
FLAGS   =   -Wall -Wextra -Werror
SRC_DIR =	./src
OBJ_DIR =	./obj
SRC     =   $(SRC_DIR)/ft_atoi.c \
			$(SRC_DIR)/error_managament.c \
			$(SRC_DIR)/checker.c \
			$(SRC_DIR)/eat.c \
			$(SRC_DIR)/monitor.c \
			$(SRC_DIR)/set_argumants.c \
			$(SRC_DIR)/get_time.c

OBJS	=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
MAIN	=	$(SRC_DIR)/main.c

all:    			$(NAME)
$(NAME):			$(MAIN) $(OBJS)
					@mkdir -p ./bin
					$(CC) $(FLAGS) $^ -o ./bin/$@

$(OBJ_DIR)/%.o: 	$(SRC_DIR)/%.c
					@mkdir -p $(OBJ_DIR)
					$(CC) $(FLAGS) -c $< -o $@

clean:
					rm -rf $(OBJ_DIR) $(MAIN_EXECUTABLE)

fclean:				clean
					rm -rf ./bin

re:					fclean all
.PHONY:				all clean fclean re