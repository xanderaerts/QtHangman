FROM ubuntu:22.04

RUN apt-get update

RUN apt-get install -y \
    autoconf \
    automake \
    autopoint \
    bash \
    bison \
    bzip2 \
    flex \
    g++ \
    g++-multilib \
    gettext \
    git \
    gperf \
    intltool \
    libc6-dev-i386 \
    libgdk-pixbuf2.0-dev \
    libltdl-dev \
    libssl-dev \
    libtool-bin \
    libxml-parser-perl \
    lzip \
    make \
    openssl \
    p7zip-full \
    patch \
    perl \
    python3 \
    python3-mako \
    ruby \
    sed \
    unzip \
    wget \
    xz-utils

RUN ln -s /usr/bin/python3 /usr/bin/python

RUN mkdir build
WORKDIR /build

RUN git clone https://github.com/mxe/mxe.git



RUN cd mxe && make download-qtbase --jobs=4

RUN cd mxe && make qtbase MXE_TARGETS='x86_64-w64-mingw32.static i686-w64-mingw32.static' MXE_USE_CCACHE= --jobs=12


ENV PATH /build/mxe/usr/bin:$PATH
#RUN export PATH=/build/mxe/usr /usr/bin:$PATH

#RUN /build/mxe/usr/i686-w64-mingw32.static/qt5/bin/qmake