# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enveryilmaz <enveryilmaz@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 10:48:13 by hdeniz            #+#    #+#              #
#    Updated: 2024/12/01 15:14:29 by enveryilmaz      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: up

up:
	@docker pull postgres:latest
	@docker pull python:3.11-slim-buster
	@docker pull debian:bullseye
	@docker-compose up --build

down:
	@# @docker stop $(shell docker ps -q) || echo No dockers are active
	@docker-compose down
	@docker-compose down --volumes

c: clean
clean: down
	@docker volume rm postgresqp || true
	@docker image rm ft_transcendence_frontend --force
	@docker image rm ft_transcendence_backend --force
	@docker image rm ft_transcendence_database --force

fc: fclean
fclean: clean
	@docker builder prune --all --force
	@docker system prune --all --force

re: down up

.PHONY: all up down c clean fc fclean re