FROM ubuntu:22.04

# This Dockerfile will be an on-demand builder for flux, with the entrypoint being a script that runs bash
# after building flux

ENV DEBIAN_FRONTEND=noninteractive
# from root:
# docker build -t ghcr.io/flux-framework/flux-python -f src/bindings/python/Dockerfile .
# docker run -it ghcr.io/flux-framework/flux-python

RUN apt-get update \
 && apt-get -qq install -y --no-install-recommends \
        automake \
        libsodium-dev \
        libzmq3-dev \
        libczmq-dev \
        libjansson-dev \
        libmunge-dev \
        libncursesw5-dev \
        lua5.4 \
        liblua5.4-dev \
        liblz4-dev \
        libsqlite3-dev \
        uuid-dev \
        libhwloc-dev \
        libmpich-dev \
        libs3-dev \
        libevent-dev \
        libarchive-dev \
        python3 \
        python3-dev \
        python3-pip \
        python3-sphinx \
        libtool \
        git \
        build-essential \
        wget \
        # Flux security
        libjson-glib-1.0.0 \ 
        libjson-glib-dev \ 
        libpam-dev && \
        ldconfig && \
        rm -rf /var/lib/apt/lists/*

WORKDIR /code

# Add flux-security directory
RUN git clone https://github.com/flux-framework/flux-security /code/security && \
    cd /code/security && \
    ./autogen.sh && \    
    ./configure --prefix=/usr/local && \
    make && \
    make install && \
    ldconfig

WORKDIR /code
