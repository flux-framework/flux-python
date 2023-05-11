#!/bin/bash

# This will install flux-core and flux-security into the
# alma image.

here=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
root=$(dirname $here)
ls

FLUX_REPO=$(cat ./flux-repo)
FLUX_BRANCH=$(cat ./flux-branch)
FLUX_RELEASE_VERSION=$(cat ./flux-release-version)

echo "repo: $FLUX_REPO"
echo "branch: $FLUX_BRANCH"
echo "release: $FLUX_RELEASE_VERSION"

git clone -b ${FLUX_BRANCH} ${FLUX_REPO} /tmp/flux-core || git clone https://github.com/flux-framework/flux-core /tmp/flux-core
mv /tmp/flux-core/src/bindings/python/flux ./flux
export FLUX_REPO FLUX_BRANCH FLUX_RELEASE_VERSION

yum -y update \
 && yum -y install epel-release \
 && yum -y install \
	wget \
	man-db \
	less \
	xz \
	lbzip2 \
        fftw-devel \
        fftw \
	git \
	curl \
	bind-utils \
	sudo \
	munge \
	ccache \
	lua \
	valgrind \
	jq \
	which \
	file \
	unzip \
	vim \
	patch \
	diffutils \
	pkgconfig \
	libtool \
	autoconf \
	automake \
	gcc-gfortran \
	gcc \
	gcc-c++ \
	make \
	cmake \
	bison \	
	flex \
	python36 \
	python3-devel \
	python3-six \
	python3-yaml \
	python3-jsonschema \
	python3-sphinx \
	libsodium-devel \
        libyaml-devel \
        libgomp \
	zeromq-devel \
	czmq-devel \
	jansson-devel \
	munge-devel \
	ncurses-devel \
	lz4-devel \
	sqlite-devel \
        boost-devel \
	libuuid-devel \
	hwloc-devel \
	lua-devel \
        libedit-devel \
	valgrind-devel \
	libs3-devel \
	systemd-devel \
	libarchive-devel \
	pam-devel \
        openssh-server \
        openssh-clients \
	perl-Time-HiRes \
	lua-posix \
	libfaketime \
	cppcheck \
	enchant \
	aspell \
	aspell-en \
	sudo \
	glibc-langpack-en \
	hwloc \
 && yum clean all

ln -fs /usr/local/bin/python3.8 /usr/bin/python3
printf "LANG=C.UTF-8" > /etc/locale.conf

# Assuming installing to /usr
export LD_LIBRARY_PATH=/usr/lib
    
# Full clone in case...
git clone https://github.com/flux-framework/flux-core ~/flux-core
cd ~/flux-core
./autogen.sh
./configure --prefix=/usr
make
make install
    
git clone https://github.com/flux-framework/flux-security ~/security
cd ~/security
./autogen.sh
./configure --prefix=/usr
make
make install
ldconfig
