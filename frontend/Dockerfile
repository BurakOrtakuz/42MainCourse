# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enveryilmaz <enveryilmaz@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/22 12:48:13 by hdeniz            #+#    #+#              #
#    Updated: 2024/12/01 15:42:30 by enveryilmaz      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:bullseye
RUN set -eux ; echo 'Acquire::Retries "5";' > /etc/apt/apt.conf.d/80-retries
ARG DOMAIN_NAME
ARG CERTS_KEY
ARG CERTS_CRT
RUN apt -y update && apt -y upgrade
RUN apt -y install nginx openssl
RUN openssl req -x509 -sha256 -nodes \
	-newkey rsa:4096 \
	-days 365 \
	-subj "/C=TR/ST=Kocaeli/L=Gebze/O=BV/OU=goiw/CN=${DOMAIN_NAME}" \
	-keyout ${CERTS_KEY} \
	-out ${CERTS_CRT}
#RUN sed -i 's/ssl_protocols.*/ssl_protocols TLSv1.3;/' /etc/nginx/nginx.conf
#COPY ./PUBLIC /var/www/html/PUBLIC
#RUN chown -R www-data:www-data /var/www/html/PUBLIC && chmod -R 755 /var/www/html/PUBLIC
COPY ./NGINX_CONFIGS/https.conf /etc/nginx/conf.d/
RUN sed -i "s|!DOMAIN_NAME!|${DOMAIN_NAME}|g" \
	/etc/nginx/conf.d/https.conf
RUN sed -i "s|!KEY_PATH!|${CERTS_KEY}|g" /etc/nginx/conf.d/https.conf
RUN sed -i "s|!CRT_PATH!|${CERTS_CRT}|g" /etc/nginx/conf.d/https.conf
COPY ./NGINX_CONFIGS/http.conf /etc/nginx/conf.d/
RUN sed -i "s|!KEY_PATH!|${CERTS_KEY}|g" /etc/nginx/conf.d/http.conf
RUN sed -i "s|!CRT_PATH!|${CERTS_CRT}|g" /etc/nginx/conf.d/http.conf
RUN sed -i "s|!DOMAIN_NAME!|${DOMAIN_NAME}|g" \
	/etc/nginx/conf.d/http.conf
EXPOSE 443
EXPOSE 80
ENTRYPOINT	[ "nginx", "-g", "daemon off;" ]
