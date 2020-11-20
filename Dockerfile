FROM ubuntu:latest
MAINTAINER stratmann a.stratmann@fz-juelich.de

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y
RUN apt-get install -y apt-utils
RUN apt-get install -y build-essential software-properties-common cmake
RUN apt-get install -y libcairo2-dev libcairomm-1.0-dev
RUN apt-get install -y libboost-test-dev
RUN apt-get install -y qt5-default qtbase5-dev qttools5-dev qtwebengine5-dev

WORKDIR /home
ADD cmake /home/cmake
ADD include /home/include
ADD src /home/src
ADD ui /home/ui
ADD test /home/test
ADD images/logo.png /home/moovie.png
ADD CMakeLists.txt /home/CMakeLists.txt
ADD moovie_config.h.cmake /home/moovie_config.h.cmake
ADD README.md /home/README.md

RUN mkdir build

WORKDIR /home/build
RUN cmake .. -DCMAKE_PREFIX_PATH=/usr/local -DBUILD_DOCUMENTATION=OFF
RUN cmake --build .
RUN make test
RUN make install

WORKDIR /home
CMD moovie-desktop