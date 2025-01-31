#!/bin/bash

PYTHON_VERSION=${1:-3.11}

sudo apt-get update && sudo apt-get install -y curl

# Install mamba for different python versions
# Python - instead of a system python we install mamba
curl -L https://github.com/conda-forge/miniforge/releases/download/24.11.3-0/Miniforge3-24.11.3-0-Linux-x86_64.sh > mambaforge.sh
chmod +x ./mambaforge.sh
sudo bash mambaforge.sh -b -p /opt/conda
rm mambaforge.sh
sudo /opt/conda/bin/mamba create --name build --yes python=${PYTHON_VERSION}
sudo /opt/conda/bin/mamba activate build

# This is intended to run in the container
echo "Building Python version ${version}"
/opt/conda/envs/build/bin/python3 -m pip install cffi ply six pyyaml jsonschema
sudo chown -R $(id -u) /opt/conda
