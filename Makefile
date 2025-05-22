NAME = push_swap
FLAG = -Wall -Wextra -Werror
SRC = stack.c \
		r_operators.c \
		rr_operators.c \
		s_p_operators.c \
		utils.c \
		ft_split.c \
		error_management.c \
		sort_utils.c \
		push_swap.c \
		check_data.c

OBJ = $(SRC:.c=.o)  

all: $(NAME)
$(NAME):
	gcc $(FLAG) -c $(SRC)
	gcc $(FLAG) $(OBJ) main.c -o $(NAME)
clean:
	/bin/rm -f  *.o
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all
.PHONY: all bonus clean fclean reerror_management.c