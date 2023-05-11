#!/bin/bash

echo "repo: $FLUX_REPO"
echo "branch: $FLUX_BRANCH"
git clone https://github.com/flux-framework/flux-core /tmp/flux-core
mv /tmp/flux-core/src/bindings/python/flux ./flux

