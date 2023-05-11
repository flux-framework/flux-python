#!/bin/bash

# Install mamba for different python versions
# Python - instead of a system python we install mamba
curl -L https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-Linux-x86_64.sh > mambaforge.sh
chmod +x ./mambaforge.sh
sudo bash mambaforge.sh -b -p /opt/conda
rm mambaforge.sh
/opt/conda/bin/pip install --upgrade --ignore-installed coverage cffi ply six pyyaml jsonschema
sudo chown -R vscode /opt/conda