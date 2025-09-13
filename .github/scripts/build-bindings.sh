#!/bin/bash

here=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
FLUX_REPO=${1:-0}
FLUX_BRANCH=${2:-3.11}

echo "Flux Repo: ${FLUX_REPO}"
echo "Flux Branch: ${FLUX_BRANCH}"
        
# Use default values if inputs are empty
FLUX_REPO_URL=${FLUX_REPO:-"https://github.com/flux-framework/flux-core"}
FLUX_BRANCH_NAME=${FLUX_BRANCH:-"master"}

git clone -b ${FLUX_BRANCH_NAME} ${FLUX_REPO_URL} /tmp/flux-core
mv /tmp/flux-core/src/bindings/python/flux ./flux        
python setup.py sdist

# I think ldconfig is Linux-specific
sudo ldconfig || echo "Not running on Linux"
