# Use the official Python image
FROM python:3.10-slim

# Set the working directory
#WORKDIR /app

ARG POSTGRES_USER
ARG POSTGRES_PASSWORD
ARG POSTGRES_DB
ARG SALT
ARG SECRET_KEY
ARG INTRA_OAUTH_URL
ARG INTRA_UID
ARG INTRA_REDIRECT_URL
ARG INTRA_TOKEN_URL
ARG INTRA_SECRET
ARG INTRA_USER_URL
ARG EMAIL_HOST
ARG EMAIL_PORT
ARG EMAIL_HOST_USER
ARG EMAIL_HOST_PASSWORD

ENV POSTGRES_USER=$POSTGRES_USER 
ENV POSTGRES_PASSWORD=$POSTGRES_PASSWORD
ENV POSTGRES_DB=$POSTGRES_DB
ENV SALT=$SALT
ENV SECRET_KEY=$SECRET_KEY
ENV INTRA_OAUTH_URL=$INTRA_OAUTH_URL
ENV INTRA_UID=$INTRA_UID
ENV INTRA_REDIRECT_URL=$INTRA_REDIRECT_URL
ENV INTRA_TOKEN_URL=$INTRA_TOKEN_URL
ENV INTRA_SECRET=$INTRA_SECRET
ENV INTRA_USER_URL=$INTRA_USER_URL
ENV EMAIL_HOST=$EMAIL_HOST
ENV EMAIL_PORT=$EMAIL_PORT
ENV EMAIL_HOST_USER=$EMAIL_HOST_USER
ENV EMAIL_HOST_PASSWORD=$EMAIL_HOST_PASSWORD

# Install system dependencies required for your packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    libpq-dev \
    python3-dev \
    redis-server \
    && rm -rf /var/lib/apt/lists/*

# Upgrade pip
RUN pip install --upgrade pip

# Copy the requirements file first (to leverage Docker caching for dependencies)
COPY requirements.txt requirements.txt

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Copy the project files
#COPY ./Backend/apiTest /TEST

# Expose the port the app runs on
EXPOSE 8000
EXPOSE 587
WORKDIR /TEST

# Run the server
ENTRYPOINT service redis-server start && python manage.py runserver 0.0.0.0:8000
#ENTRYPOINT tail -F /dev/null 