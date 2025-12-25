#!/bin/bash

# Exit on error, unset variable, or pipe failure
set -euo pipefail

# This must be set
PYTHON_VERSION=${1:-py311}

# These will be empty for nightly test, and we will clone master branch
FLUX_RELEASE_VERSION=${2:-0.78.0}
FLUX_VERSION=${3:-0.78.0}

if [[ "$(uname)" == "Darwin" ]]; then
  brew install zeromq libsodium epoll-shim libev
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
          libtool \
          git \
          build-essential \
          libpam-dev

  sudo rm -rf /var/lib/apt/lists/*
  sudo ldconfig

  # Set the dynamic library path variable for Linux.
  export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib
  echo "LD_LIBRARY_PATH: ${LD_LIBRARY_PATH}"
fi

echo "Found Python $(which python3)"
echo "PATH: ${PATH}"

# Here we can start common setup (we hope)
echo "Flux Version for pypi is ${FLUX_VERSION}"
if [[ "$(uname)" == "Darwin" ]]; then
  PIXI_ROOT=/Users/runner/work/flux-python/flux-python/.pixi
  PIXI_ENV=${PIXI_ROOT}/envs/${PYTHON_VERSION}
  sed -i '' "s/version = \"0.0.0\"/version = \"$FLUX_VERSION\"/" pyproject.toml
  echo $(find /Users/runner/ -name python3) || echo $(find /Users/runner/ -name python)

  # Tell where to look for lua.h
  CPPFLAGS="-I${PIXI_ENV}/include"
  
  # This makes me want to kill homebrew and MacOS with fire.
  # I know most of these aren't required. I can't remove them because of the ❤️‍🔥
  export PYTHON_SITE_PACKAGES=$(find ${PIXI_ENV} -name site-packages)
  export PYTHON_EXEC_PREFIX=${PYTHON_SITE_PACKAGES}
  export PYTHON_SITE_PKG=${PYTHON_SITE_PACKAGES}
  export PYTHON_PLATFORM_SITE_PKG=${PYTHON_SITE_PACKAGES}
  export PYTHON_SITELIB=${PYTHON_SITE_PACKAGES}
  export PYTHON_PREFIX=${PYTHON_SITE_PACKAGES}
  export PKG_CONFIG_PATH=${PIXI_ENV}/lib/pkgconfig
  export PYTHONDIR=${PYTHON_SITE_PACKAGES}
  
  # Set these to empty.
  export PYTHON_EXTRA_LDFLAGS=" "
  export PYTHON_EXTRA_LIBS=" "

  echo "PKG_CONFIG_PATH: ${PKG_CONFIG_PATH}"
  echo "PYTHON_PREFIX: ${PYTHON_PREFIX}"
  echo "PYTHON_SITE_PACKAGES: ${PYTHON_SITE_PACKAGES}"
  echo "PYTHON_EXEC_PREFIX: ${PYTHON_EXEC_PREFIX}"
else
  PIXI_ROOT=/home/runner/work/flux-python/flux-python/.pixi
  export PIXI_ENV=${PIXI_ROOT}/envs/${PYTHON_VERSION}
  sed -i "s/version = \"0.0.0\"/version = \"$FLUX_VERSION\"/" pyproject.toml
  CPPFLAGS="-I${PIXI_ENV}/include"
fi

# Can we remove need for setuptools?
export PYTHON=${PIXI_ENV}/bin/python3
export PYTHON_EXECUTABLE=${PIXI_ENV}/bin/python3
export PYTHON_NOVERSIONCHECK=yes
export LUA_CFLAGS="-I${PIXI_ENV}/include"
export LDFLAGS="-L${PIXI_ENV}/lib -L${PIXI_ENV}/lib64" 
echo "Found lua.h in:\n$(find ${PIXI_ROOT} -name lua.h)" || echo "Did not find lua.h"

# Store current directory
here=$(pwd)
luarocks install luaposix

# Flux Security --
# Does not have a variant for Mac
if [[ "$(uname)" != "Darwin" ]]; then
  
  # Install munge and libmunge
  MUNGE_VERSION="0.5.16"
  curl -L "https://github.com/dun/munge/releases/download/munge-${MUNGE_VERSION}/munge-${MUNGE_VERSION}.tar.xz" -o munge.tar.xz
  tar -xf munge.tar.xz
  cd "munge-${MUNGE_VERSION}"
  ./configure --prefix=/usr
  make
  sudo make install
  cd ..

  git clone https://github.com/flux-framework/flux-security ~/security
  cd ~/security
  ./autogen.sh
  ./configure --prefix=/usr/local
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

  # Mac you are a JERK
  ZMQ_PREFIX=$(brew --prefix zeromq)
  SODIUM_PREFIX=$(brew --prefix libsodium)
  LIBEV_PREFIX=$(brew --prefix libev)
  EPOLL_SHIM_PREFIX=$(brew --prefix epoll-shim)

  CPPFLAGS="-I'"$EPOLL_SHIM_PREFIX"'/include -I'"$LIBEV_PREFIX"'/include -I'"$ZMQ_PREFIX"'/include -I'"$SODIUM_PREFIX"'/include -I$PIXI_ENV/include"
  CPPFLAGS="-I$(brew --prefix libev)/include ${CPPFLAGS}"
  export CPPFLAGS="-I$(brew --prefix epoll-shim)/include/libepoll-shim ${CPPFLAGS}"
  export LDFLAGS="$LDFLAGS -L'"$EPOLL_SHIM_PREFIX"'/lib -L'"$LIBEV_PREFIX"'/lib -L'"$SODIUM_PREFIX"'/lib -L'"$ZMQ_PREFIX"'/lib -Wl,-rpath,'"$SODIUM_PREFIX"'/lib -Wl,-rpath,$PIXI_ENV/lib"
  CPPFLAGS="$CPPFLAGS" CFLAGS="${CPPFLAGS}" LDFLAGS="${LDFLAGS}" PKG_CONFIG_PATH=$PKG_CONFIG_PATH ./configure --prefix=/usr/local --with-external-libev || (cp ./config.log ../ && exit 1)

  # Surgery. This is the biggest hairball ever - you can't build libsodium / zeromq from source because it doesn't detect curve+libsodium.
  # You also can't use easily from Homebrew without this hack. I can't even believe I figured this out!
  find . -name "Makefile" -exec sed -i.bak "s/^\(LIBS = .*\)$/\1 -lepoll-shim/" {} +
  make -j  || (cp ./config.log ../ && exit 1)
  sudo make install  || (cp ./config.log ../ && exit 1)
else
  ./configure CPPFLAGS="$CPPFLAGS" CFLAGS="${CPPFLAGS}" LDFLAGS="${LDFLAGS}" --prefix=/usr/local
  cp ./config.log ../
  make VERBOSE=1
  sudo make install || true
  sudo make install
  sudo ldconfig
fi

cd "${here}"
