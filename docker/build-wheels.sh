#!/bin/bash

here=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
build_number=${1:-0}

# Create python environments for each version we want to release!
# We wrap like this because this script can be used locally, but
# in GitHub actions we want to do in a matrix
for version in 3.6 3.7 3.8 3.9 3.10; do
    /bin/bash $here/build-wheel.sh ${version} ${build_number}
done
