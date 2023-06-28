# Flux Python Bindings

> 🐍️ You called me?

Hello! You've found the flux Python bindings, an experiment to build and deploy
Flux to Pypi without needing to store code alongside Flux. The goal of
this experiment is to test them separately. This was originally developed
at [vsoch/flux-python](https://github.com/vsoch/flux-python) and has 
been ported here to automate more officially. The following guides might be useful
to you:

 - ⭐️ [Flux Framework Documentation](https://flux-framework.readthedocs.io)
 - ⭐️ [Flux Projects](https://flux-framework.org)
 - ⭐️ [Tutorials](https://flux-framework.readthedocs.io/en/latest/tutorials/index.html)
 - ⭐️ [Installing Flux Python on an LLNL System](https://github.com/flux-framework/flux-python/blob/main/LLNL.md) 
 

## Helper Install

If you don't want to figure out your flux version and install with pip directory (per instructions in [manual install](#manual-install))
we provide a helper script [install-flux-python.sh](script/install-flux-python.sh) that will:

1. Determine that Flux and Python are installed with pip
2. Parse the version of Flux on your PATH
3. Derive the version and run the command for you!

You'll first want to make sure that flux is on your path, as is a `python3` executable with pip installed
as a module alongside it. And you can run it as follows:

```bash
wget https://raw.githubusercontent.com/flux-framework/flux-python/main/script/install-flux-python.sh
chmod +x ./install-flux-python.sh
./install-flux-python.sh
```

If a version is missing on pypi or you otherwise have a bug, please open an issue here.

## Manual Install

Since we need to link to Flux libraries, you are advised to install flux and flux-security in the same location
that will be discovered via the executable "flux," so typically `/usr` or `/usr/local`. You will need `wheel` installed:

```bash
$ pip install wheel
```

You can do either:

```bash
# Find the flux version on your system
flux --version

# Install the bindings that match that version
pip install flux-python==0.48.0
```

And if you are having trouble with the WCI cache, you can also wget the [file directly from pypi](https://pypi.org/project/flux-python/#history)
and install the .tar.gz directly.

```bash
wget https://files.pythonhosted.org/packages/25/fb/02951d80e44a19db291f0e7370d4e7d82c0c1b17709a37913881f958dff7/flux-python-0.48.0rc0.tar.gz
pip install flux-python-0.48.0rc0.tar.gz
```

If you install to a local (personal) location (e.g., `$HOME/.local`) you'll need to add this to your `PYTHONPATH`

```bash
# The directory "flux" is under the site-packages here
export PYTHONPATH=$HOME/.local/lib/python3.7/site-packages
```

You can then do some basic testing.

```bash
$ flux start --test-size=4
```

**Ensure your PYTHONPATH is correct here** And import flux.

```bash
$ ipython
```
```python
import flux
flux.Flux()
```
 
 
## Development

We provide a [.devcontainer](https://github.com/flux-framework/flux-python/tree/main/.devcontainer) environment you can open in VSCode
to have an environment ready to go with Flux (and Flux Security). You can follow
the instructions in the DevContainer to build the Flux Python bindings.
By default, this environment installs the latest flux-core.
If you want to build a custom version with Flux core you can do:

```bash
rm -rf ~/flux-core
export FLUX_VERSION=0.49.0
wget https://github.com/flux-framework/flux-core/releases/download/v${FLUX_VERSION}/flux-core-${FLUX_VERSION}.tar.gz
tar -xzvf flux-core-${FLUX_VERSION}.tar.gz
sudo mv flux-core-${FLUX_VERSION} ~/flux-core
rm flux-core-${FLUX_VERSION}.tar.gz
cd ~/flux-core
./configure --prefix=/usr
make
sudo make install
```

And then copy over the Python source to "flux" and build your custom archives and/or wheels:

```bash
$ rm -rf /workspaces/flux-python/flux
$ cp -R src/bindings/python/flux /workspaces/flux-python/flux
$ cd /workspaces/flux-python
# Archive
$ python3 setup.py sdist

# Wheel (will build for the python version you've targeted)
# This isn't currently being done but is a future TODO!
$ python3 setup.py sdist bdist_wheel
```

You can build versions of the Python wheels across 3.6 to 3.10 like:

```bash
# only need to run this once in the container
/bin/bash ./docker/install-mamba.sh

# And this to install the current Flux + version in setup.py as a wheel
# The number is the build number
/bin/bash ./docker/build-wheels.sh 2
```

And if you want to upload:

```bash
$ twine upload dist/*.tar.gz
```


### Automation

In order to (eventually) support a workflow to check for a release, get the release's
flux assets and build, we have a [workflow script](.github/scripts/check_releases.py) that will:

- Get the latest flux releases
- Compare to the latest pypi releases
- If there is a new release (from Flux on GitHub) not in pypi, build and release

And the script also can take an optional version string that will find and build
a version explicitly. You might (to test) do:

```bash
$ export GITHUB_TOKEN=xxxxxxxxxxxxx
$ python .github/scripts/check_releases.py flux-framework --version 0.46.0
```

That basically checks if there should be a build. It will use the container provided
here to install a custom version of flux core that builds the release.

#### Release

SPDX-License-Identifier: LGPL-3.0

LLNL-CODE-764420
