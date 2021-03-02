#!/bin/bash

# Set default arguments
DOCKERFILE_LOC=$(pwd)
VOLUME_LOC=/home/$USER

# Print usage
usage()
{
  echo "Usage: moovie-desktop-docker.sh [ -d | --dockerfile-loc DOCKERFILE LOCATION ]
                                [ -v | --volume-loc VOLUME LOCATION]"
}

# Parse command line arguments
while [[ $# -gt 0 ]]
do
  case "$1" in
    -d | --dockerfile-loc) DOCKERFILE_LOC=$2; shift 2;;
    -v | --volume-loc) VOLUME_LOC=$2; shift 2;;
    -h | --help) usage; exit 0;;
    *) echo "Unexpected option: $1"; usage; exit 1;;
  esac
done

# Build docker image if not already build
if [[ "$(docker images -q moovie-desktop 2>/dev/null)" == "" ]]
then
  # Resolve full dockerfile location path
  DOCKERFILE_LOC=$(readlink -e $DOCKERFILE_LOC)
  echo "Using docker file location \"$DOCKERFILE_LOC\""

  echo "Building docker image (This can take a while)"
  docker build -t moovie-desktop $DOCKERFILE_LOC > /dev/null
fi

# Resolve full volume path
VOLUME_LOC=$(readlink -e $VOLUME_LOC)
echo "Include volume $VOLUME_LOC"

# Run docker image with moovie-desktop
echo "Run docker image"
docker run \
  --user "$(id -u)" \
  --workdir "$(pwd)" \
  --volume /home/$USER/:/home/$USER \
  --volume /tmp/.X11-unix:/tmp/.X11-unix \
  --env DISPLAY="$DISPLAY" \
  moovie-desktop 2> /dev/null
