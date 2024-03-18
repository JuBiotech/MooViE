Installation and Setup
==========

### Prerequisites and Dependencies
These prerequisites are only necessary if you want to install MooViE natively. This is currently only supported for
Linux. The listed pacakges refer to Debian/Ubuntu. For other systems, see below section about how to install MooViE using Docker.

Required tools:
* GNU C++ compiler
* CMake (>= 3.7, recommended `cmake-curses-gui` or `cmake-qt-gui`)

Required Libraries:
- `libfreetype-dev`
- `libsigc++-2.0-dev`
- `libcairo2-dev`
- `libcairomm-1.0-dev`
- Either Qt5 libraries (`qtbase5-dev`, `qttools5-dev`, `libqt5svg5-dev`, `libgl1-mesa-dev`) or Qt6 libraries (`qt6-base-dev`, `qt6-tools-dev`, `libqt6svg6-dev`, `libgl1-mesa-dev`)

For running the tests:
- `libboost-test-dev`
- `gcovr`

For building the documentation:
- `doxygen`
- `graphviz`
- `python3-sphinx`
- `python3-sphinx-book-theme`
- `python3-exhale`

### Installation

There are two ways to install MooViE for your operating system. The recommended and more generic way is to use _Docker_
in combination with X11. For Ubuntu operating systems (>= 20.04), MooViE can also be installed manually.

#### Docker
To simplify the installation procedure we supply two scripts that install and run Docker containers in which the
graphical user interface of MooViE runs. It can be displayed on the host machine via X11 connection. The scripts are
located in the project directory root. Prior to installing and running MooViE with the scripts, you need to install
Docker (for instance by following this
[instruction](https://docs.docker.com/engine/install/ubuntu/#install-docker-engine)).

On Linux systems with X11 server installed and running you just need to open a bash console and run the
installation/runner script with
```shell script
./moovie-desktop-docker.sh [-d Dockerfile location] [-v Volume location]
```
On Windows systems, you additionally need to install an Xserver
(check out [vcxsrv](https://sourceforge.net/projects/vcxsrv/)) and run it with disabled access control
([helpful tutorial](https://medium.com/@potatowagon/how-to-use-gui-apps-in-linux-docker-container-from-windows-host-485d3e1c64a3)).
Being set up, you can now open a Powershell console and run the Windows installation/runner script with
```powershell
./moovie-desktop-docker.ps1 [-d Dockerfile location] [-v Volume to mount]
```

Both scripts will build the Docker image and run it afterward. For later runs, the script will check if the image is
already installed and just run it directly.

#### Manual
After installing the dependencies from above using `apt-get`, you can simply follow the installation steps for MooViE 
from the Dockerfile.

To build MooViE for a single user with Qt6, the following is sufficient

```bash
mkdir build-local
cd build-local
cmake .. -DCMAKE_PREFIX_PATH=~/.local -DBUILD_GUI=ON -DQT_VERSION=QT6 -DBUILD_TESTS=OFF -DBUILD_DOCUMENTATION=OFF
cmake --build . -j
make install
