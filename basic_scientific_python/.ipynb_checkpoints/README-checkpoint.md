# To get exactly the same environment we used in the lectures

(Assumes that you have a GPU for the GPU packages.)

**Step 1:** install Mambaforge (dependency manager for all the software we'll be using).

```bash
wget https://github.com/conda-forge/miniforge/releases/latest/download/Mambaforge-Linux-x86_64.sh
bash Mambaforge-Linux-x86_64.sh
```

Answer the questions:

  1. "Press ENTER to continue" (do it)
  2. "Do you accept the license terms?": "yes"
  3. "Mambaforge will now be installed into this location": accept the default by pressing enter
  4. "Do you wish the installer to initialize Mambaforge by running conda init": "yes"

**Step 2:** log out of the shell that you're using and back in again (or open a new one).

**Step 3:** create an environment from `environment.yml`, which installs all of the software.

```bash
mamba env create -f environment.yml
```
**Step 4:** enter this environment (every time you open a shell) with `mamba activate` or `conda activate`.

```bash
mamba activate 2024-07-29-ml_tutorial
```

**Step 5:** launch JupyterLab like this:

```bash
jupyter lab
```

# To get a similar environment

See [environment.yml](environment.yml). Each of these are are package names and versions. After setting up Mambaforge (steps 1 and 2, above), you can select individual packages to install with

```python
mamba install PACKAGE-NAME
```

Without specifying a version number, you'll get the latest mutually compatible set of packages (probably what you want). The version numbers in [environment.yml](environment.yml) are for reproducing exactly the environment we had at the time of the tutorial.
