#!/bin/bash

cat << EOF
  __ _                             _   _                 
 / _| |_   ___  __     _ __  _   _| |_| |__   ___  _ __  
| |_| | | | \ \/ /____| '_ \| | | | __| '_ \ / _ \| '_ \ 
|  _| | |_| |>  <_____| |_) | |_| | |_| | | | (_) | | | |
|_| |_|\__,_/_/\_\    | .__/ \__, |\__|_| |_|\___/|_| |_|
                      |_|    |___/               Installer

Report bugs to: https://github.com/flux-framework/flux-python

Flux Python is still being tested, and not all versions are present!
If you need to request a new version added, please open an issue at
the repository above.
EOF

sleep 3

# Determine if flux is on the path
check_installed() {
    printf "\n⭐️ Checking for install of ${1}...\n"
    if hash ${1} 2>/dev/null; then
        echo "Found ${1} install"
        ${1} --version
    else
        echo "${1} not found installed to PATH."
        exit 1
    fi
}

# Check that pip is installed, retrieved as a python module directory
check_installed_pip() {
    printf "\n⭐️ Checking for pip install...\n"

    python3 -m pip --version
    if [[ $? -ne 0 ]]; then
        echo "python3 -m pip command failed. Ensure pip is installed."
        exit 1
    fi
}

# Ensure flux and python3 on the path
# Anyone using python 2 still needs to go and question their life choices.
check_installed flux
check_installed python3

# Ensure we have pip (python3 -m pip)
check_installed_pip

# Determine the flux version
full_version=$(flux version | grep -Po '(?<=commands:)[^;]+' | sed -e 's/^[ \t]*//')
printf "\n⭐️ Found full version of flux ${full_version}\n"

# If we have a git/long version, derive the partial version - just the junk after the -
if [[ "$full_version" == *"-"* ]]; then
    full_version=(${full_version//-/ })
fi

printf "\n⭐️ Attempting install of flux-python==${full_version}\n"
echo "python3 -m pip install flux-python==${full_version}"
python3 -m pip install flux-python==${full_version}
