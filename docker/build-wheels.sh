#!/bin/bash

here=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
build_number=${1:-0}
version=${2:-3.11}

# This is intended to run in the container
echo "Building Python version ${version}"

# Build the bindings for this python version!
python3 setup.py sdist
python3 setup.py bdist_wheel --plat-name=any --build-number=${build_number}
ls ./dist
