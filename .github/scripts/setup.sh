#!/bin/bash

set -euo pipefail

# This will be empty for nightly test, and we will clone master branch
FLUX_RELEASE_VERSION=${FLUX_RELEASE_VERSION:-0.50.0}
FLUX_VERSION=${FLUX_VERSION:-develop}

# Prepare the version file
echo "Flux Version for pypi is ${FLUX_VERSION}"
sed -i "s/package_version = \"develop\"/package_version = \"$FLUX_VERSION\"/" setup.py

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
        lua5.3 \
        liblua5.3-dev \
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
echo "Flux Release Version is ${FLUX_RELEASE_VERSION}"
echo "Flux version requested to build is ${FLUX_RELEASE_VERSION}"
wget https://github.com/flux-framework/flux-core/releases/download/v${FLUX_RELEASE_VERSION}/flux-core-${FLUX_RELEASE_VERSION}.tar.gz
tar -xzvf flux-core-${FLUX_RELEASE_VERSION}.tar.gz
sudo mv flux-core-${FLUX_RELEASE_VERSION} /code

sudo chown -R $USER /code
cd /code
chmod +x etc/gen-cmdhelp.py

# This is only needed for non-releases
./autogen.sh || echo "No autogen here"
./configure --prefix=/usr/local

# We don't really care about the version here -just building python bindings
make VERBOSE=1

# This sometimes fails the first time but then works ok? Weird
sudo make install || true
sudo make install
sudo ldconfig   
cd ${here}
