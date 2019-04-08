FROM ubuntu:18.04

#install packages from apt (when image is built)  
RUN apt-get update --fix-missing
RUN apt-get install -y \
    build-essential \
    libstdc++-7-dev \
    libgtest-dev \
    cmake \
    git \
    python3 \
    python3-pip 

VOLUME /project

