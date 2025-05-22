FROM postgres:latest
ARG POSTGRES_USER
ARG POSTGRES_PASSWORD
ARG POSTGRES_DB
ENV POSTGRES_USER=${POSTGRES_USER}
ENV POSTGRES_PASSWORD=${POSTGRES_PASSWORD}
ENV POSTGRES_DB=${POSTGRES_DB}
RUN set -eux ; echo 'Acquire::Retries "5";' > /etc/apt/apt.conf.d/80-retries
COPY create_database.sql /docker-entrypoint-initdb.d/create_database.sql
RUN chmod -R 777 /var/lib/postgresql/data
RUN chmod -R 777 /var/lib/postgresql
#COPY SqlCreate.sh /docker-entrypoint-initdb.d/SqlCreate.sh
EXPOSE 5432