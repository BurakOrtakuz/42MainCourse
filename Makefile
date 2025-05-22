NAME	= ircserv

CFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRC		=	./srcs/Bot.cpp \
			./srcs/Channel.cpp \
			./srcs/Client.cpp \
			./srcs/GuessBot.cpp \
			./srcs/main.cpp \
			./srcs/Server.cpp \
			./srcs/ServerUtils.cpp \
			./srcs/commands/BOT.cpp \
			./srcs/commands/CAP.cpp \
			./srcs/commands/JOIN.cpp \
			./srcs/commands/KICK.cpp \
			./srcs/commands/MODE.cpp \
			./srcs/commands/NICK.cpp \
			./srcs/commands/PART.cpp \
			./srcs/commands/PASS.cpp \
			./srcs/commands/PRIVMSG.cpp \
			./srcs/commands/QUIT.cpp \
			./srcs/commands/USER.cpp \
			./srcs/commands/Utils.cpp \
			./srcs/commands/WHO.cpp \

OBJ = $(SRC:.cpp=.o)

CC		=	c++

RM		=	rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re: fclean all

run: all 
	./$(NAME);

.PHONY: all clean fclean re run