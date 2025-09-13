#!/bin/bash

# Exit on error, unset variable, or pipe failure
set -euo pipefail

# This will be empty for nightly test, and we will clone master branch
FLUX_RELEASE_VERSION=${FLUX_RELEASE_VERSION:-0.78.0}
FLUX_VERSION=${FLUX_VERSION:-0.78.0}

if [[ "$(uname)" == "Darwin" ]]; then
  brew install \
    autoconf \
    automake \
    libtool \
    make \
    pkg-config \
    epoll-shim \
    libev \
    zeromq \
    jansson \
    lz4 \
    libarchive \
    hwloc \
    sqlite \
    lua \
    luarocks \
    cffi \
    libyaml \
    jq

  # Possibility - install munge with MacPorts
  # sudo port install munge
  eval "$(/opt/homebrew/bin/brew shellenv)"

  # Set the dynamic library path variable for macOS
  export DYLD_LIBRARY_PATH=/usr/local/lib
  
  # Ensure we activate micromamabe that has a pinned version
  PIP_INSTALL="/opt/conda/bin/python3 -m pip install"
  ln -s $(which glibtoolize) /usr/local/bin/libtoolize
  
  CPPFLAGS="-I${HOMEBREW_PREFIX}/include/lua"
  CPPFLAGS="-I$(brew --prefix libev)/include ${CPPFLAGS}"
  CPPFLAGS="-I$(brew --prefix epoll-shim)/include/libepoll-shim ${CPPFLAGS}"
  # LDFLAGS=-L${HOMEBREW_PREFIX}/lib
  PKG_CONFIG_PATH=$(pkg-config --variable pc_path pkg-config)
  PKG_CONFIG_PATH=$(brew --prefix libarchive)/lib/pkgconfig:${PKG_CONFIG_PATH}
  PATH=$(brew --prefix libtool)/libexec/gnubin:$PATH
  export LD_LIBRARY_PATH="/opt/conda/envs/build/lib:/opt/conda/envs/build/lib64"

# Linux block!
else
  export DEBIAN_FRONTEND=noninteractive
  export TZ=UTC
  sudo ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ | sudo tee /etc/timezone

  sudo apt-get update
  sudo apt-get install -y \
          libjson-glib-dev \
          wget \
          curl \
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
          python3-sphinx \
          python3-cffi \
          libtool \
          git \
          build-essential \
          libpam-dev

  sudo rm -rf /var/lib/apt/lists/*
  sudo ldconfig

  # Set the dynamic library path variable for Linux. The conda path is for the container.
  export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/opt/conda/envs/build/lib
fi

# Ensure we find micromamba environment first
# mamba init commands are intolerable so let's do basics ourselves.
PIP_INSTALL="/opt/conda/envs/build/bin/python3 -m pip install"
export PATH="/opt/conda/envs/build/bin:$PATH"
export PYTHONPATH=$(find /opt/conda/envs/build -name site-packages)
export PYTHON=/opt/conda/envs/build/bin/python3
export PYTHON_PREFIX=${PYTHONPATH}
export PYTHON_EXEC_PREFIX=${PYTHONPATH}
# export LIBS="-L/opt/conda/envs/build/lib:/opt/conda/envs/build/lib64"

echo "Found Python $(which python3)"
echo "PYTHONPATH: ${PATH}"
echo "PATH: ${PATH}"
echo "LD_LIBRARY_PATH: ${LD_LIBRARY_PATH}"

# Here we can start common setup (we hope)
echo "Flux Version for pypi is ${FLUX_VERSION}"
if [[ "$(uname)" == "Darwin" ]]; then
  sed -i '' "s/version = \"0.0.0\"/version = \"$FLUX_VERSION\"/" pyproject.toml
else
  sed -i "s/version = \"0.0.0\"/version = \"$FLUX_VERSION\"/" pyproject.toml
fi
>>>>>>> 922e452 (ci: test updated main build script to add macOS)

# Store current directory
here=$(pwd)

# Install Python requirements using the OS-specific pip command - allow for ubuntu to be 24.04 or not.
# I like how "--break-system-packages" is analogous with --i-acknowledge-i-am-a-terrible-person
if [[ "$(uname)" == "Darwin" ]]; then
  echo "Installing python requirements for MacOS"
  ${PIP_INSTALL} IPython setuptools ply sphinx cffi pyyaml
  ${PIP_INSTALL} -r .github/scripts/requirements-dev.txt
else
  echo "Installing python requirements for Linux"
  ${PIP_INSTALL} IPython pyyaml || ${PIP_INSTALL} IPython --break-system-packages pyyaml
  ${PIP_INSTALL} -r .github/scripts/requirements-dev.txt || ${PIP_INSTALL} -r .github/scripts/requirements-dev.txt --break-system-packages

  # Flux Security --
  # Does not have a variant for Mac
  git clone https://github.com/flux-framework/flux-security ~/security
  cd ~/security
  ./autogen.sh
  PYTHON_PREFIX=PYTHON_EXEC_PREFIX=${PYTHON_PREFIX} PYTHON=/opt/conda/bin/python3 ./configure --prefix=/usr/local
  make
  sudo make install
  sudo ldconfig
fi

# Flux Core --
cd "${here}"
echo "Flux Release Version is ${FLUX_RELEASE_VERSION}"
wget https://github.com/flux-framework/flux-core/releases/download/v${FLUX_RELEASE_VERSION}/flux-core-${FLUX_RELEASE_VERSION}.tar.gz
tar -xzvf flux-core-${FLUX_RELEASE_VERSION}.tar.gz
cd flux-core-${FLUX_RELEASE_VERSION}
chmod +x etc/gen-cmdhelp.py

./autogen.sh || echo "No autogen here"

if [[ "$(uname)" == "Darwin" ]]; then
  CPPFLAGS="$CPPFLAGS" PKG_CONFIG_PATH=$PKG_CONFIG_PATH ./configure --prefix=/usr/local
  ls ./scripts
  ./scripts/check-macos.sh || echo "No check-macos.sh"
else
  ./configure --prefix=/usr/local
  make VERBOSE=1
  sudo make install || true
  sudo make install
  sudo ldconfig
fi

cd "${here}"
