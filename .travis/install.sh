#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    brew update || brew update
    brew outdated pyenv || brew upgrade pyenv
    brew install pyenv-virtualenv
    brew install cmake || true
    brew install python3 || brew upgrade python

    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi

    pyenv install 2.7.10
    pyenv virtualenv 2.7.10 conan
    pyenv rehash
    pyenv activate conan
elif [[ "$(uname -s)" == 'MSYS_NT-10.0' ]]; then
    choco install -y python3
fi

pip install conan --upgrade
pip install conan_package_tools

conan user
