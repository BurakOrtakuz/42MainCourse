FROM debian:bullseye

RUN apt-get update && apt-get install -y mariadb-server

COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/

COPY ./tools/dbstart.sh /

RUN chmod +x /dbstart.sh

ENTRYPOINT [ "/dbstart.sh" ]

CMD [ "mariadbd" ]