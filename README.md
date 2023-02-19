# Vector graphic editor

### Preparation

Clone repository

```bash
git clone <path to repo from bitbacket>
```

Set up a virtual environment for python and install required python packages (pre-commit)

```bash
python3 -m venv env
. env/bin/activate # env\Scripts\activate.exe - on Windows
pip install -r requirements.txt
```

### Setting up pre-commit

[Pre-commit](https://pre-commit.com/) is a framework for setting up commit hook
configurations. This repository has such a hook to automatically fix formatting
(and check various other things). It was already installed into the python
virtual environment so you can simply set it up with

```bash
pre-commit install
```
Note that this has to be done for every fresh clone of the repository.

### Run pre-commit for all files
```bash
pre-commit run --all-files
```
