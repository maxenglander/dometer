FROM debian:stable-20190610-slim

ENV BAZEL_INSTALLER_PATH /tmp/bazel-installer.sh
ENV BAZEL_INSTALLER_URL https://github.com/bazelbuild/bazel/releases/download/0.28.0/bazel-0.28.0-installer-linux-x86_64.sh
ENV BUILD_DIR /dns-telemeter/build
ENV DEBIAN_FRONTEND noninteractive
ENV PATHOGEN_URL https://tpo.pe/pathogen.vim

RUN apt-get update \
 && apt-get install -yq --no-install-recommends --no-install-suggests apt-utils

RUN apt-get install -yq --no-install-recommends --no-install-suggests \
    pkg-config zip g++ zlib1g-dev unzip python3

RUN apt-get install -yq --no-install-recommends --no-install-suggests \
    pdns-server pdns-backend-remote

RUN apt-get install -yq --no-install-recommends --no-install-suggests \
    libjsoncpp-dev

RUN apt-get install -yq --no-install-recommends --no-install-suggests \
    ca-certificates curl socat

RUN apt-get install -yq --no-install-recommends --no-install-suggests \
    universal-ctags git

RUN apt-get install -yq --no-install-recommends --no-install-suggests vim \
 && mkdir -p $HOME/.vim/autoload $HOME/.vim/bundle \
 && curl -LSso $HOME/.vim/autoload/pathogen.vim $PATHOGEN_URL \
 && git clone https://github.com/vim-scripts/c.vim $HOME/.vim/bundle/c.vim

RUN curl -fsSL $BAZEL_INSTALLER_URL -o $BAZEL_INSTALLER_PATH \
 && chmod +x $BAZEL_INSTALLER_PATH \
 && $BAZEL_INSTALLER_PATH

RUN mkdir -p $BUILD_DIR
WORKDIR $BUILD_DIR

COPY . .
RUN cp -a dotfiles/. $HOME/
RUN ctags -R --c++-kinds=+p+l

#RUN bazel build //main:dns-telemeter
CMD ["/bin/bash", "-c", "tail -f /dev/null"]
