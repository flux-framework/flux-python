#!/bin/bash

here=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
build_number=${1:-0}
version=${2:-3.11}

# This is intended to run in the container
echo "Building Python version ${version}"

export PATH=/opt/conda/envs/build/bin:$PATH
export PYTHONPATH=/opt/conda/envs/build/lib/python${version}/site-packages

/opt/conda/bin/mamba activate build || true

# Build the bindings for this python version!
/opt/conda/envs/build/bin/python3 setup.py sdist
/opt/conda/envs/build/bin/python3 setup.py bdist_wheel --plat-name=any --build-number=${build_number}
unset PYTHONPATH
