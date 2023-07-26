FROM ubuntu:22.04
MAINTAINER stratmann a.stratmann@fz-juelich.de

# Install dependencies
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update -y
RUN apt-get install -y --no-install-recommends apt-utils
RUN apt-get install -y --no-install-recommends build-essential software-properties-common cmake
RUN apt-get install -y --no-install-recommends libcairo2-dev libcairomm-1.0-dev
RUN apt-get install -y --no-install-recommends libboost-test-dev
# dependencies for Qt 5
RUN apt-get install -y --no-install-recommends qtbase5-dev qttools5-dev libqt5svg5-dev
# dependencies for Qt 6
RUN apt-get install -y --no-install-recommends qt6-base-dev qt6-tools-dev libqt6svg6-dev
RUN apt-get install -y --no-install-recommends libgl1-mesa-dev
RUN apt-get -y clean
RUN apt-get -y autoremove
RUN apt-get -y autoclean
RUN rm -rf /var/lib/apt/lists/*


# Move source code to image
WORKDIR /home
ADD cmake /home/cmake
ADD src /home/src
ADD images/logo.png /home/moovie.png
ADD CMakeLists.txt /home/CMakeLists.txt
ADD moovie_config.h.cmake /home/moovie_config.h.cmake
ADD README.md /home/README.md

# Install MooViE and run tests
RUN mkdir build
WORKDIR /home/build
RUN cmake .. -DCMAKE_PREFIX_PATH=/usr/local -DBUILD_GUI=ON -DQT_VERSION=QT6 -DBUILD_TESTS=ON -DBUILD_DOCUMENTATION=OFF
RUN cmake --build .
RUN make test
RUN make install

WORKDIR /home
CMD moovie-desktop
