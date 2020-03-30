FROM debian:stable-20190610-slim

ENV BAZEL_INSTALLER_PATH /tmp/bazel-installer.sh
ENV BAZEL_INSTALLER_URL https://github.com/bazelbuild/bazel/releases/download/2.0.0/bazel-2.0.0-installer-linux-x86_64.sh
ENV BUILD_DIR /dometer/build
ENV DEBIAN_FRONTEND noninteractive
ENV PATHOGEN_URL https://tpo.pe/pathogen.vim

RUN apt-get update \
 && apt-get install -yq --no-install-recommends --no-install-suggests \
      apt-utils \
      pkg-config \
      zip \
      g++ \
      gdb \
      valgrind \
      libtool \
      make \
      cmake \
      zlib1g-dev \
      unzip \
      python3 \
      ca-certificates \
      ctags \
      curl \
      wget \
      git \
      socat \
      procps \
      gettext \
      vim

RUN curl -fsSL $BAZEL_INSTALLER_URL -o $BAZEL_INSTALLER_PATH \
 && chmod +x $BAZEL_INSTALLER_PATH \
 && $BAZEL_INSTALLER_PATH

RUN mkdir -p $HOME/.vim/autoload $HOME/.vim/bundle \
 && curl -LSso $HOME/.vim/autoload/pathogen.vim $PATHOGEN_URL \
 && git clone https://github.com/vim-scripts/c.vim $HOME/.vim/bundle/c.vim

RUN mkdir -p $BUILD_DIR
WORKDIR $BUILD_DIR

COPY . .
RUN cp -a dotfiles/. $HOME/
RUN ctags -R --c++-kinds=+p+l

#RUN bazel build //main:dometer
CMD ["/bin/bash", "-c", "tail -f /dev/null"]
