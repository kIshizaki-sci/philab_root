
ARG BASE_CONTAINER=ishizakiss/philab-root:20210925
FROM $BASE_CONTAINER

LABEL maintainer="Kohei ISHIZAKI <ishizaki_at_phi.phys.nagoya-u_dot_ac_dot_jp>"

#########################################################
#########################################################

ARG YOUR_NAME="philab_member"
ARG YOUR_PASS="plainpassword"
ARG YOUR_UID="1000"

#########################################################
#########################################################

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

ENV DEBIAN_FRONTEND noninteractive

#########################################################
#########################################################

###
### Add user (sudo user)
###
USER root
RUN useradd --create-home -u $YOUR_UID -s /bin/bash ${YOUR_NAME}; \
    echo "${YOUR_NAME}:${YOUR_PASS}" | chpasswd; \
    adduser ${YOUR_NAME} sudo;
USER $YOUR_NAME
RUN export PATH=$HOME/.local/bin:$PATH
ENV PATH $PATH:/home/$YOUR_NAME/.local/bin

###
### 日本語化
###
USER root
RUN apt update && apt install -yq --no-install-recommends \
    language-pack-ja-base \
    language-pack-ja;\
    echo 'LANG=ja_JP.UTF-8' >> /etc/profile;
ENV LANG=ja_JP.UTF-8

###
### ROOT setting
###
USER $YOUR_NAME
ENV ROOTSYS=/usr/local/root \
    PATH=$ROOTSYS/bin:$PATH \
    PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH \
    CLING_STANDARD_PCH=none
RUN export PATH=$PATH ;\
    source ${ROOTSYS}/bin/thisroot.sh;
USER root
RUN echo 'export PATH=/usr/local/cargo/bin:$PATH' >> /etc/profile;\
    echo '. /usr/local/root/bin/thisroot.sh' >> /etc/profile;

USER root
RUN apt clean; \
    rm -rf /var/lib/apt/lists/*;

USER $YOUR_NAME
WORKDIR /home/$YOUR_NAME
RUN mkdir input output working html;

# JupyterLab settings
USER $YOUR_NAME
WORKDIR /home/$YOUR_NAME
RUN mkdir -p /home/$YOUR_NAME/.jupyter/lab;

COPY jupyterlab-settings /home/${YOUR_NAME}/.jupyter/lab/user-settings

# Jupyterlab-myst
USER root
WORKDIR /tmp
RUN git clone https://github.com/executablebooks/jupyterlab-myst.git .jupyterlab-myst;\
    cd .jupyterlab-myst;\
    pip3 install -e .;\
    jupyter labextension develop . --overwrite;\
    jlpm run build;\
    cd /tmp && rm -rd .jupyterlab-myst;

USER root
RUN jupyter notebook --generate-config;\
    jupyter lab build;