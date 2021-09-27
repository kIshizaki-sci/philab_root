
ARG BASE_CONTAINER=ubuntu:hirsute-20210825

FROM $BASE_CONTAINER

LABEL maintainer="Kohei ISHIZAKI <ishizaki_at_phi.phys.nagoya-u_dot_ac_dot_jp>"


#########################################################
#########################################################

ARG cern_root_version="v6-24-06"

#########################################################
#########################################################

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

ENV DEBIAN_FRONTEND noninteractive

USER root
RUN dpkgArch="$(dpkg --print-architecture)"; \
        case "${dpkgArch##*-}" in \
            amd64) perl -p -i.bak -e 's%(deb(?:-src|)\s+)https?://(?!archive\.canonical\.com|security\.ubuntu\.com)[^\s]+%$1http://ftp.riken.go.jp/Linux/ubuntu/%' /etc/apt/sources.list;; \
        esac;

RUN apt update && \
    apt upgrade -y --no-install-recommends \
    && apt install -y --install-recommends \
    curl \
    git \
    sudo \
    wget;

# https://github.com/nodesource/distributions
RUN curl -fsSL https://deb.nodesource.com/setup_lts.x | bash - ;
RUN apt install -yq --no-install-recommends \
    cmake \
    ca-certificates \
    emacs \
    locales \
    fonts-liberation \
    run-one \
    build-essential \
    python3-dev \
    vim-tiny \
    inkscape \
    libsm6 \
    libxext-dev \
    libxrender1 \
    lmodern \
    netcat \
    nodejs \
    tzdata \
    unzip \
    nano-tiny \
    python3-pip \
    llvm \
    llvm-12-dev;

RUN apt install -yq --no-install-recommends \
    texlive-xetex \
    texlive-fonts-recommended \
    texlive-plain-generic;

## Install ROOT prerequired
RUN apt install -yq --no-install-recommends \
    dpkg-dev \
    binutils \
    libx11-dev \
    libxpm-dev \
    libxft-dev \
    libxext-dev \
    libssl-dev \
    gfortran \
    libpcre3-dev \
    xlibmesa-glu-dev \
    libglew1.5-dev \
    libftgl-dev \
    libmysqlclient-dev \
    libfftw3-dev \
    libcfitsio-dev \
    graphviz-dev \
    libavahi-compat-libdnssd-dev \
    libldap2-dev \
    libxml2-dev \
    libkrb5-dev \
    libhdf5-dev \
    libgsl0-dev;

###
###  Install Python packages
###

COPY requirements.txt /tmp/
USER root
RUN pip3 install -I pip; \
    pip3 install -r /tmp/requirements.txt; \
    rm /tmp/requirements.txt; \
    jupyter server extension enable --user --py jupyterlab_git; \
    jupyter lab build; \
    python3 -m bash_kernel.install;

###
### Install ROOT
###

USER root
ARG root_prefix="/usr/local/root"
RUN cd /tmp && mkdir .root && cd .root; \
    git clone --progress https://github.com/root-project/root.git -b ${cern_root_version};
RUN cd /tmp/.root; \
    mkdir root_build ${root_prefix} && cd root_build; \
    dpkgArch="$(dpkg --print-architecture)"; \
    case "${dpkgArch##*-}" in \
        amd64) cmake -DCMAKE_INSTALL_PREFIX=${root_prefix} ../root; cmake --build . -- install -j4;; \
        arm64) cmake  -Dimt=OFF -Dbuiltin_tbb=OFF -DCMAKE_INSTALL_PREFIX=${root_prefix} ../root; cmake --build . -- install -j2;; \
        *) echo >&2 "unsupported architecture: ${dpkgArch}"; exit 1 ;; \
    esac; \
    export PATH=${ROOTSYS}/bin:$PATH ; \
    echo "source ${root_prefix}/bin/thisroot.sh" >> ~/.bashrc;

ENV ROOTSYS=${root_prefix} \
    PATH=$ROOTSYS/bin:$PATH \
    PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH \
    CLING_STANDARD_PCH=none
RUN cp -r ${root_prefix}/etc/notebook/kernels/root /usr/local/share/jupyter/kernels; \
    jupyter notebook --generate-config; \
    rm -rd /tmp/.root; \
    echo ${root_prefix}/lib >> /etc/ld.so.conf; \
    ldconfig;

EXPOSE 8888 6006

USER root
RUN apt clean; \
    rm -rf /var/lib/apt/lists/*;
