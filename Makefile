.PHONY: all clean fclean stop up

all: file up

file:
	test -d /home/bortakuz/data || mkdir /home/bortakuz/data
	test -d /home/bortakuz/data/wordpress || mkdir /home/bortakuz/data/wordpress
	test -d /home/bortakuz/data/mariadb || mkdir /home/bortakuz/data/mariadb

re: fclean all

clean:
	@docker-compose -f srcs/docker-compose.yml down

fclean: clean
	@docker system prune -af
	@rm -rf /home/bortakuz/data

up:
	docker-compose -f ./srcs/docker-compose.yml up --build