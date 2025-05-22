FLAG = -Wall -Wextra -Werror -g

all:
	@echo Derlendi
	@gcc $(FLAG) server.c -o server
	@gcc $(FLAG) client.c -o client
	@rm -rf server.dSYM
	@rm -rf client.dSYM
	@rm -rf server_bonus
	@rm -rf client_bonus
bonus:
	@echo Bonus derlendi
	@gcc $(FLAG) server_bonus.c -o server_bonus
	@gcc $(FLAG) client_bonus.c -o client_bonus
	@rm -rf server_bonus.dSYM
	@rm -rf client_bonus.dSYM
	@rm -rf server
	@rm -rf client
run: all
	@./server
brun: bonus
	@./server_bonus
clean:
	@echo Temizlendi
	@rm -rf server
	@rm -rf client
	@rm -rf server_bonus
	@rm -rf client_bonus
fclean: clean
re: fclean all
.PHONY: all bonus clean fclean