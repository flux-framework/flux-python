#!/bin/bash

here=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
root=$(dirname $here)

FLUX_REPO=$(cat ./flux-repo)
FLUX_BRANCH=$(cat ./flux-branch)
FLUX_RELEASE_VERSION=$(cat ./flux-release-version)
echo "repo: $FLUX_REPO"
echo "branch: $FLUX_BRANCH"
echo "release: $FLUX_RELEASE_VERSION"

git clone https://github.com/flux-framework/flux-core /tmp/flux-core
mv /tmp/flux-core/src/bindings/python/flux ./flux
export FLUX_REPO FLUX_BRANCH FLUX_RELEASE_VERSION
/bin/bash $root/.github/scripts/setup.sh
