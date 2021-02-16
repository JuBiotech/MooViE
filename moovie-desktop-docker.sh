#!/bin/bash

# Build docker image if not already build
if [[ "$(docker images -q moovie-desktop 2>/dev/null)" == "" ]]
then
  # Set the docker file path
  DOCKERFILE_LOC=$(pwd)
  if [[ $# -gt 1 ]]; then
    DOCKERFILE_LOC=$1
  fi
  echo "Using docker file location \"$DOCKERFILE_LOC\""

  echo "Building docker image (This can take a while)"
  docker build -t moovie-desktop $DOCKERFILE_LOC > /dev/null
fi

# Run docker image with moovie-desktop
echo "Run docker image"
docker run \
  --user "$(id -u)" \
  --workdir "$(pwd)" \
  --volume /home/$USER/:/home/$USER \
  --volume /tmp/.X11-unix:/tmp/.X11-unix \
  --env DISPLAY=$DISPLAY \
  moovie-desktop 2> /dev/null
