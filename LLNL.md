# Flux Python on LLNL Systems

> 🐍️ You called me?

**Important** these bindings are under development, and we are still working on automation
and improvement! If you run into an issue, please [let us know](https://github.com/flux-framework/flux-python/issues) 
so that we can fix. 

Are you looking for specific instructions for your system at LLNL? You've
come to the right place! If your Python install or system is missing from here,
please [let us know](https://github.com/flux-framework/flux-python/issues).

## How does it work?

If you are installing the .tar.gz (from source) we try to link to Flux libraries by way of finding the main `flux` binary,
and then assuming Flux and other dependencies are located in that discovered tree. 
This typically means `/usr` or `/usr/local`. Note that since the Python bindings were done
after releases 0.46.0 through 0.49.0, we needed to make some patches to imports,
and the patches are build from [here](https://github.com/rse-ops/flux-core-python).

For the wheels (not done yet) we will assume the install in `/usr`.

## 1. Install for Your System

### TCE

> E.g., Corona!

On Corona we provide support for the following Python versions:

```bash
$ ls -1 /usr/tce/packages/python/
python
python-3.10.8
python-3.9.12
```

We provide support for anything above Python 3 (not 2.x).

### Find your Flux version

You should first find the right version of Flux:

```bash
$ flux --version
commands:               0.49.0
libflux-core:           0.49.0
libflux-security:       0.8.0
build-options:          +ascii-only+hwloc==2.8.0+zmq==4.3.4
```

And then find the pypi package of the same version from [here](https://pypi.org/project/flux-python/).
And then ensure that your python of interest is active on the path, and you've created a virtual environment
(that will have pip) that you can install to. Here is a very "hard coded" way to go about it. Most likely
you would just add your Python of interest to your `PATH` but here we are targeting the binary directly.
Also note that (sometimes) you can install a slight variation of version (e.g., here we are installing 0.48.0 to 0.49.0,
and this is possible because the Flux Python interfaces didn't change.

```bash
# Python 3.10
/usr/tce/packages/python/python-3.10.8/bin/python -m venv python310env
source ./python310env/bin/activate
# ~/test/python310env/bin/python
# ~/test/python310env/bin/pip
pip install flux-python==0.48.0rc6
# In your flux instance make sure to export PYTHONPATH to your environment
export PYTHONPATH=~/test/python310env/lib/python3.10/site-packages

# Python 3.9.x
/usr/tce/packages/python/python-3.9.12/bin/python -m venv python39env
source ./python39env/bin/activate
# ~/test/python39env/bin/python
# ~/test/python39env/bin/pip
pip install flux-python==0.48.0rc6
# In your flux instance make sure to export PYTHONPATH to your environment
export PYTHONPATH=~/test/python39env/lib/python3.9/site-packages
```

For any of the approaches above, there seems to be some kind of cluster cache. If you have trouble with the cache
finding a variant, you can wget the .tar.gz and install as follows:

```bash
wget https://files.pythonhosted.org/packages/25/fb/02951d80e44a19db291f0e7370d4e7d82c0c1b17709a37913881f958dff7/flux-python-0.48.0rc0.tar.gz
pip install flux-python-0.48.0rc0.tar.gz
```

### Tioga

> This also would work on rzvernal and Tenaya, or so I've been told!

You will find the following Python versions:

```bash
$ module spider python
```
```console
---------------------------------------------------------------------------------------------------------------------
  python:
---------------------------------------------------------------------------------------------------------------------
     Versions:
        python/2.7.18
        python/3.9.12
        python/3.10.8
     Other possible modules matches:
        cray-python
```

We provide support for anything above Python 3 (not 2.x).


### Find your Flux version

You should first find the right version of Flux:

```bash
$ flux --version
commands:               0.49.0
libflux-core:           0.49.0
libflux-security:       0.8.0
build-options:          +ascii-only+hwloc==2.8.0+zmq==4.3.4
```

And then find the pypi package of the same version from [here](https://pypi.org/project/flux-python/).
And then ensure that your python of interest is loaded as a module. Note that these python modules
also come with pip, so we don't need to make an environment to get it. Yay!

```bash
# Python 3.9.x
$ module load python/3.9.12
pip install flux-python==0.49.0rc0
# In your flux instance make sure to export PYTHONPATH to your environment
export PYTHONPATH=~/.local/lib/python3.9/site-packages

# Python 3.9.x
$ module load python/3.10.8
pip install flux-python==0.48.0rc6
# In your flux instance make sure to export PYTHONPATH to your environment
export PYTHONPATH=~/.local/lib/python3.10/site-packages
```

For any of the approaches above, there seems to be some kind of cluster cache. If you have trouble with the cache
finding a variant, you can wget the .tar.gz and install as follows:

```bash
wget https://files.pythonhosted.org/packages/25/fb/02951d80e44a19db291f0e7370d4e7d82c0c1b17709a37913881f958dff7/flux-python-0.48.0rc0.tar.gz
pip install flux-python-0.48.0rc0.tar.gz
```

## 2. Python path

Likely the module will be installed to an environment or personal location, and this is really important because
you'll need to add the location to your `PYTHONPATH`. As an example, when you start a flux instance:

```bash
$ flux start --test-size=4
```

Flux is going to set the `PYTHONPATH` to be where the Flux install is.

```bash
$ echo $PYTHONPATH
/usr/lib64/flux/python3.6
```

**We don't want this!** We need to target where we just installed! In this case, it was to an environment:

```bash
# The directory "flux" is under the site-packages where you installed
# **Make sure to update this to your environment location!**
$ export PYTHONPATH=~/test/python310env/lib/python3.10/site-packages
```

But it also could be to your `local` user Python install (if you didn't use an environment):

```bash
# The directory "flux" can also be under a site-packages in your local pythonsite
# Make sure you choose the right python version subdirectory!
export PYTHONPATH=$HOME/.local/lib/python3.7/site-packages
```

### Testing

Once you are in a Flux instance and flux-python is on your path, I like to test with a simple job submission. Here
is a quick script:

```python
#!/usr/bin/env python3

import flux
import flux.job

jobspec = flux.job.JobspecV1.from_command(['echo', 'hello', 'bacon', 'pancakes!'])
future = flux.job.submit_async(flux.Flux(), jobspec)
print("Submit job %s" % future)
```

You can wget the script from the repository here directly:

```bash
wget https://raw.githubusercontent.com/flux-framework/flux-python/main/tests/submit_job.py
```

And try running the script...

```bash
$ python3 submit_job.py 
```
```console
Submit job <flux.job.submit.SubmitFuture object at 0x155542e3c2b0>
```

And then inspecting the output!

```bash
(python310env) (python310env) [fluxuser@corona111]$ flux jobs -a
       JOBID USER     NAME       ST NTASKS NNODES     TIME INFO
   f2dVLA9nP sochat1  echo       CD      1      1   0.248s corona211
```

Are we makin' pancakes?

```bash
$ flux job attach $(flux job last)
```
```console
hello bacon pancakes!
```

Absolutely.