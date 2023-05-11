#!/bin/bash

here=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

version=${1}

if [[ "${version}" == "" ]]; then
    echo "Version must be provided as script argument"
    exit
fi

# This is intended to run in the container
echo "Building Python version ${version}"
/opt/conda/bin/mamba create -y -p /tmp/py${version} python==${version}
/opt/conda/bin/mamba install -y -q -p /tmp/py${version} cffi ply six pyyaml jsonschema
export PATH=/tmp/py${version}/bin:$PATH
export PYTHONPATH=/tmp/py${version}/lib/python3.6/site-packages

# Build the bindings for this python version!
python3 setup.py sdist bdist_wheel
unset PYTHONPATH