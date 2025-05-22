FROM debian:bullseye

RUN apt-get update && apt-get install -y php-fpm php-mysql sendmail wget

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp-cli

COPY ./conf/www.conf /etc/php/7.4/fpm/pool.d/

COPY ./tools/wordpress_options.sh /

RUN chmod +x /wordpress_options.sh

ENTRYPOINT [ "/wordpress_options.sh" ]

CMD [ "/usr/sbin/php-fpm7.4", "--nodaemonize" ]