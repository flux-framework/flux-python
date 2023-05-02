# Flux Python Bindings

Hello! You've found the flux Python bindings, an experiment to build and deploy
Flux to Pypi without needing to store code alongside Flux. The goal of
this experiment is to test them separately. This was originally developed
at [vsoch/flux-python](https://github.com/vsoch/flux-python) and has 
been ported here to automate more officially.

## Development

We provide a [.devcontainer](.devcontainer) environment you can open in VSCode
to have an environment ready to go with Flux (and Flux Security). You can follow
the instructions in the DevContainer to build the Flux Python bindings.

### Building Modules

We will need to build the tarball providing paths to the flux-core and flux-security
sources. This can be improved upon to just be one path if all the dependencies
are provided with the flux install (and we don't need the source):


```bash
# Generate the wheel (requires pip install wheel)
$ python3 setup.py sdist bdist_wheel --flux-root /home/vscode/flux-core --security-src /home/vscode/security --security-include /usr/local/include/flux/security
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

More coming soon! We still need to:

 - [ ] some version checking
 - [ ] ability to build .tar.gz (needed flux deps to be removed)


