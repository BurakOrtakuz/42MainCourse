# Start from the Debian Bullseye image
FROM debian:bullseye

# Install necessary packages
RUN apt-get update && apt-get install -y \
    nginx \
    openssl 
    #\&& rm -rf /var/lib/apt/lists/*

# Copy nginx configuration file
#RUN chmod 777 ./conf/nginx.conf
COPY ./conf/nginx.conf /etc/nginx/nginx.conf

# Generate a private key and a self-signed certificate
RUN openssl genrsa -out /etc/nginx/server.key 2048 \
    && openssl req -new -x509 -key /etc/nginx/server.key -out /etc/nginx/server.crt -days 365 -subj "/CN=${DOMAIN_NAME}" -subj /CN=localhost

# Start Nginx when the container has provisioned.
CMD ["nginx", "-g", "daemon off;"]