NAME := minishell
CC := gcc
CF := -Wall -Wextra -Werror -ggdb
FILES := ./src/builtins/buildin-coms.c\
		./src/builtins/buildin_coms-cd.c\
		./src/builtins/buildins.c\
		./src/builtins/export.c\
		./src/builtins/export_utils.c\
		./src/builtins/export_utils2.c\
		./src/checks/input_check.c\
		./src/checks/input_check2.c\
		./src/errors/errors.c\
		./src/errors/errors_2.c\
		./src/executer/executer_utils.c\
		./src/executer/ft_execute.c\
		./src/expand/expand_env.c\
		./src/expand/expand_env_utils.c\
		./src/frees/execution_frees.c\
		./src/frees/frees.c\
		./src/frees/void_frees.c\
		./src/init_processes.c\
		./src/main.c\
		./src/parser/command.c\
		./src/parser/lexer_utils.c\
		./src/parser/parse_comms.c\
		./src/parser/parser_utils.c\
		./src/parser/quotes.c\
		./src/parser/quotes2.c\
		./src/parser/tokens.c\
		./src/redirs/ft_connect_pipes.c\
		./src/redirs/heredoc.c\
		./src/redirs/open_redirections.c\
		./src/signals.c\
		./src/utils/array_utils.c\
		./src/utils/array_utils2.c\
		./src/utils/env_utils.c\
		./src/utils/find_in_path.c\
		./src/utils/matrix_util.c
OBJ := $(FILES:.c=.o)
LIBFT := ./libft/libft.a

all: $(NAME)

$(NAME) : $(OBJ)
	@make -C ./libft
	@$(CC) $(CF) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean : go
	@rm -rf $(OBJ)

go :
	@rm -rf *.o
	@rm -rf ./obj/*.o

fclean : clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re go

