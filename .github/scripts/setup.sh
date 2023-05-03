#!/bin/bash

set -euo pipefail

# This will be empty for nightly test, and we will clone master branch
FLUX_VERSION=${FLUX_VERSION:-0.48.0}
echo "Flux Version is ${FLUX_VERSION}"

here=$(pwd)
sudo apt-get update
sudo apt-get install -y \
        libjson-glib-dev \
        wget \
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
        libpam-dev

sudo ldconfig
sudo rm -rf /var/lib/apt/lists/*

sudo python3 -m pip install IPython
sudo python3 -m pip install -r .github/scripts/requirements-dev.txt
export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib

git clone https://github.com/flux-framework/flux-security ~/security
cd ~/security
./autogen.sh
./configure --prefix=/usr/local
make 
sudo make install
sudo ldconfig

# This is a build from a release 
if [[ "${FLUX_VERSION}" != "" ]]; then
    echo "Flux version requested to build is ${FLUX_VERSION}"
    wget https://github.com/flux-framework/flux-core/releases/download/v${FLUX_VERSION}/flux-core-${FLUX_VERSION}.tar.gz
    tar -xzvf flux-core-${FLUX_VERSION}.tar.gz
    sudo mv flux-core-${FLUX_VERSION} /code

# Build from the current master branch
else
    sudo git clone https://github.com/flux-framework/flux-core /code
fi
sudo chown -R $USER /code
cd /code
chmod +x etc/gen-cmdhelp.py

# This is only needed for non-releases
./autogen.sh || echo "No autogen here"
./configure --prefix=/usr/local
make
sudo make install
sudo make install
sudo ldconfig   
cd ${here}
