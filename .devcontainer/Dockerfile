FROM fluxrm/testenv:focal

LABEL maintainer="Vanessasaurus <@vsoch>"

# Match the default user id for a single system so we aren't root
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=1000
ENV USERNAME=${USERNAME}
ENV USER_UID=${USER_UID}
ENV USER_GID=${USER_GID}

# Pip not provided in this version
RUN apt-get update
COPY .github/scripts/requirements-dev.txt /requirements.txt

# For easier Python development.
RUN apt-get update && \
    apt-get install -y libjson-glib-dev && \
    python3 -m pip install IPython && \
    python3 -m pip install -r /requirements.txt

# Assuming installing to /usr/local
ENV LD_LIBRARY_PATH=/usr/local/lib

# Assuming installing to /usr/local
ENV LD_LIBRARY_PATH=/usr/local/lib

# extra interactive utilities and compilation_database generation
RUN apt-get update \
 && apt-get -qq install -y --no-install-recommends \
    bear \
    fd-find \
    gdb \
    less \
    ripgrep
    
# Install Go
RUN wget https://go.dev/dl/go1.20.2.linux-amd64.tar.gz && \
    tar -C /usr/local -xzf go1.20.2.linux-amd64.tar.gz

ENV PATH=$PATH:/usr/local/go/bin
# Add the group and user that match our ids
RUN groupadd -g ${USER_GID} ${USERNAME} && \
    adduser --disabled-password --uid ${USER_UID} --gid ${USER_GID} --gecos "" ${USERNAME} && \
    echo "${USERNAME} ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers
USER $USERNAME

# Full clone in case...
RUN git clone https://github.com/flux-framework/flux-core ~/flux-core && \
    cd ~/flux-core && \
    ./autogen.sh && \
    ./configure --prefix=/usr/local && \
    make && \
    sudo make install
    
RUN git clone https://github.com/flux-framework/flux-security ~/security && \
    cd ~/security && \
    ./autogen.sh && \    
    ./configure --prefix=/usr/local && \
    make && \
    sudo make install && \
    sudo ldconfig
