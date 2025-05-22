NAME = libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = ./src/ft_convert/ft_atoi.c \
		./src/ft_convert/ft_itoa.c \
		./src/ft_is/ft_isalnum.c \
		./src/ft_is/ft_isalpha.c \
		./src/ft_is/ft_isascii.c \
		./src/ft_is/ft_isdigit.c \
		./src/ft_is/ft_isprint.c \
		./src/ft_is/ft_tolower.c \
		./src/ft_is/ft_toupper.c \
		./src/ft_list/ft_lstadd_back.c \
		./src/ft_list/ft_lstadd_front.c \
		./src/ft_list/ft_lstclear.c \
		./src/ft_list/ft_lstdelone.c \
		./src/ft_list/ft_lstiter.c \
		./src/ft_list/ft_lstlast.c \
		./src/ft_list/ft_lstmap.c \
		./src/ft_list/ft_lstnew.c \
		./src/ft_list/ft_lstsize.c \
		./src/ft_mem/ft_bzero.c \
		./src/ft_mem/ft_calloc.c \
		./src/ft_mem/ft_memchr.c \
		./src/ft_mem/ft_memcmp.c \
		./src/ft_mem/ft_memcpy.c \
		./src/ft_mem/ft_memmove.c \
		./src/ft_mem/ft_memset.c \
		./src/ft_output/ft_putchar_fd.c \
		./src/ft_output/ft_putendl_fd.c \
		./src/ft_output/ft_putnbr_fd.c \
		./src/ft_output/ft_putstr_fd.c \
		./src/ft_printf/ft_printf.c \
		./src/ft_split/ft_split.c \
		./src/ft_split/my_split.c \
		./src/ft_str/ft_strchr.c \
		./src/ft_str/ft_strdup.c \
		./src/ft_str/ft_strdup2.c \
		./src/ft_str/ft_strdup3.c \
		./src/ft_str/ft_striteri.c \
		./src/ft_str/ft_strjoin.c \
		./src/ft_str/ft_strjoin_free.c \
		./src/ft_str/ft_strlcat.c \
		./src/ft_str/ft_strlcpy.c \
		./src/ft_str/ft_strlcpy2.c \
		./src/ft_str/ft_strlen.c \
		./src/ft_str/ft_strmapi.c \
		./src/ft_str/ft_strncmp.c \
		./src/ft_str/ft_strnstr.c \
		./src/ft_str/ft_strrchr.c \
		./src/ft_str/ft_strtrim.c \
		./src/ft_str/ft_substr.c \
		./src/ft_str/ft_substr2.c \
		./src/get_next_line/get_next_line.c


OBJS = ft_atoi.o \
       ft_itoa.o \
       ft_isalnum.o \
       ft_isalpha.o \
       ft_isascii.o \
       ft_isdigit.o \
       ft_isprint.o \
       ft_tolower.o \
       ft_toupper.o \
       ft_lstadd_back.o \
       ft_lstadd_front.o \
       ft_lstclear.o \
       ft_lstdelone.o \
       ft_lstiter.o \
       ft_lstlast.o \
       ft_lstmap.o \
       ft_lstnew.o \
       ft_lstsize.o \
       ft_bzero.o \
       ft_calloc.o \
       ft_memchr.o \
       ft_memcmp.o \
       ft_memcpy.o \
       ft_memmove.o \
       ft_memset.o \
       ft_putchar_fd.o \
       ft_putendl_fd.o \
       ft_putnbr_fd.o \
       ft_putstr_fd.o \
	   ft_printf.o \
       ft_split.o \
	   my_split.o \
       ft_strchr.o \
       ft_strdup.o \
	   ft_strdup2.o \
	   ft_strdup3.o \
       ft_striteri.o \
       ft_strjoin.o \
	   ft_strjoin_free.o \
       ft_strlcat.o \
       ft_strlcpy.o \
	   ft_strlcpy2.o \
       ft_strlen.o \
       ft_strmapi.o \
       ft_strncmp.o \
       ft_strnstr.o \
       ft_strrchr.o \
       ft_strtrim.o \
       ft_substr.o \
	   ft_substr2.o \
	   get_next_line.o


all : $(NAME)

$(NAME) :
		@$(CC) $(FLAGS) -c $(SRCS)
		@ar rcs $(NAME) $(OBJS)

clean:
	@rm -f  $(OBJS)

fclean:
	@rm -f  $(OBJS)
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
