#!/bin/bash

here=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
build_number=${1:-0}
version=${2:-3.11}
glibc=${MANYLINUX_GLIBC:-2_17}

# This is intended to run in the container
echo "Building Python version ${version}"
echo "Build number ${build_number}"

export PATH=/opt/conda/envs/build/bin:$PATH
export PYTHONPATH=/opt/conda/envs/build/lib/python${version}/site-packages

/opt/conda/bin/mamba activate build || true

# Build the bindings for this python version!
/opt/conda/envs/build/bin/python3 setup.py sdist
arch=$(/opt/conda/envs/build/bin/python3 -c 'import sysconfig; print(sysconfig.get_platform().replace("-", "_").replace(".", "_").split("linux_", 1)[1])')
/opt/conda/envs/build/bin/python3 setup.py bdist_wheel --plat-name=manylinux_${glibc}_${arch} --build-number=${build_number}
unset PYTHONPATH
