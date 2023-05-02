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
 
 
## Development

We provide a [.devcontainer](https://github.com/flux-framework/flux-python/tree/main/.devcontainer) environment you can open in VSCode
to have an environment ready to go with Flux (and Flux Security). You can follow
the instructions in the DevContainer to build the Flux Python bindings.
By default, this environment installs the latest flux-core.
If you want to build a custom version with Flux core you can do:

```bash
rm -rf ~/flux-core
export FLUX_VERSION=0.46.0
wget https://github.com/flux-framework/flux-core/releases/download/v${FLUX_VERSION}/flux-core-${FLUX_VERSION}.tar.gz
tar -xzvf flux-core-${FLUX_VERSION}.tar.gz
sudo mv flux-core-${FLUX_VERSION} ~/flux-core
rm flux-core-${FLUX_VERSION}.tar.gz
cd ~/flux-core
./configure --prefix=/usr/local
make
sudo make install
```

And then build your custom wheel:

```bash
$ cd /workspaces/flux-python
$ python3 setup.py sdist bdist_wheel --flux-root /home/vscode/flux-core --security-src /home/vscode/security --security-include /usr/local/include/flux/security --version 0.46.0-rc-0
```

And if you want to upload:

```bash
$ twine upload dist/*.tar.gz
```

### Building Modules

We will need to build the tarball providing paths to the flux-core and flux-security
sources. This can be improved upon to just be one path if all the dependencies
are provided with the flux install (and we don't need the source). Note
that we also provide a custom version for the pypi package:

```bash
# Generate the wheel (requires pip install wheel)
$ python3 setup.py sdist bdist_wheel --flux-root /home/vscode/flux-core --security-src /home/vscode/security --security-include /usr/local/include/flux/security --version 0.46.0-rc-0
```

You can then install the wheel (as a user or to the root)

```bash
$ pip install dist/flux-0.46.0-cp38-cp38-linux_x86_64.whl --user
$ sudo pip install dist/flux-0.46.0-cp38-cp38-linux_x86_64.whl 
```
```console
Processing ./dist/flux-0.46.0-cp38-cp38-linux_x86_64.whl
Requirement already satisfied: cffi>=1.1 in /usr/lib/python3/dist-packages (from flux==0.46.0) (1.14.0)
Installing collected packages: flux
Successfully installed flux-0.46.0
```

If the development container you are using still installs the Python bindings, you'll want to do the sudo variant above to override.
And then start a flux instance:

```bash
$ flux start --test-size=4
```

And import flux.

```bash
$ ipython
```
```python
import flux
flux.Flux()
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

### Work in Progress

@vsoch wants to try installing her test releases to a system somewhere, and figure
out this issue with buidling a wheel (or maybe we don't want wheels after all):

> HTTPError: 400 Bad Request from https://upload.pypi.org/legacy/        
>         Binary wheel 'flux_python-0.46.0rc0-cp38-cp38-linux_x86_64.whl' has an 
>         unsupported platform tag 'linux_x86_64'. 

#### Release

SPDX-License-Identifier: LGPL-3.0

LLNL-CODE-764420
