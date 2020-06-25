# Building Cairo

- Download and unpack zlib, libpng, pixman, cairo, libsig++, glib, freetype++ and cairomm
- Install Visual Studio Community edition
- install Cmake ([https://cmake.org/download/](https://cmake.org/download/))
- Download and install QT5
    - use the offline installer and cut internet connection, so no registration is required
- We assume that you have administrative privileges, but everything can also be done as a regular user, you just have to adjust the paths

- install MSYS2 
    - follow instructions from [https://www.msys2.org/](https://www.msys2.org/)
    - install make there: `pacman -S make gettext base-devel`
- Open a Developer command prompt for Visual Studio
- Set the path to include MSYS2 and cmake
    - `set PATH=%PATH%;C:\msys64\usr\bin\;"C:\Program Files\CMake\bin\"`
- Build zlib
    - luckily zlib has support for CMake
    - enter the zlib directory
    - `mkdir build` and `cd build`
    - `cmake -A Win32 ..`
    - `msbuild zlib.vcxproj`
    - have an VS cmd with admin privileges ready and run go to the build dir and run `msbuild INSTALL.vcxproj`
- Build libpng
    - again CMake support
    - enter the zlib directory
    - `mkdir build` and `cd build`
    - `cmake -A Win32 ..`
    - `msbuild png.vcxproj`
    - in an admin shell `msbuild INSTALL.vcxproj`

- Build pixman
    - `make -f Makefile.win32 pixman "CFG=release"`
- Modify cairos buildsystem (`build/Makefile.win32.common`)
    - for zlib
        - `ZLIB_PATH :=  /c/Program\ Files\ \(x86\)/zlib/`
        - `ZLIB_CFLAGS += -I$(ZLIB_PATH)/include/`
        - `CAIRO_LIBS += $(ZLIB_PATH)/lib/zlibd.lib`
    - for libpng
        - `LIBPNG_PATH :=  /c/Program\ Files\ \(x86\)/libpng/`
        - `LIBPNG_CFLAGS += -I$(LIBPNG_PATH)/include/`
        - `CAIRO_LIBS +=  $(LIBPNG_PATH)/lib/libpng16d.lib`
- Build cairo
    - `make -f Makefile.win32 "CFG=release" "PIXMAN_PATH=../pixman-0.38.4"`
    - do as you are told and copy some files (admin shell)
        - `mkdir "C:\Program Files (x86)\cairo"`
        - `mkdir "C:\Program Files (x86)\cairo\lib"`
        - `mkdir "C:\Program Files (x86)\cairo\include"`
        - `mkdir "C:\Program Files (x86)\cairo\include\cairo"`
        - `cp cairo-version.h src\cairo-features.h src\cairo.h src\cairo-deprecated.h src\cairo-win32.h src\cairo-script.h src\cairo-ps.h src\cairo-pdf.h src\cairo-svg.h "C:\Program Files (x86)\cairo\include\cairo"`
        - `cp src\release\cairo.dll src\release\cairo-static.lib src\release\cairo.lib "C:\Program Files (x86)\cairo\lib"`
	- MooViEs CMake build system uses pkgconfig to find software, so to make our lives easier we write configuration file for cairo and put it in a location where pkgconfig will find it (`C:\msys64\usr\share\pkgconfig\cairo.pc
`)


    prefix=C:/Program Files (x86)/cairo
    exec_prefix=C:/Program Files (x86)/cairo
    libdir=C:/Program Files (x86)/cairo/lib
    sharedlibdir=C:/Program Files (x86)/cairo/lib
    includedir=C:/Program Files (x86)/cairo/include
    
    Name: cairo
    Description: Multi-platform 2D graphics library
    Version: 1.16.0
    
    Requires:
    Libs: -L${libdir} -lcairo
    Cflags: -I${includedir}/cairo


# Building Cairomm
- Build sig++
    - `mkdir build_local` and `cd build_local`
    - `cmake -A Win32 ..`
    - `msbuild ALL_BUILD.vcxproj`
    - in the admin shell `msbuild INSTALL.vcxproj`

- Build Cairomm
    - in the glib dir `cp msvc_recommended_pragmas.h %MY_INC%`
    - `cp -r "C:\Program Files (x86)\sigc++\include\sigc++-3.0\sigc++" "C:\Progam Files (x86)\lib\sigc++-3.0\include\sigc++config.h" %MY_INC%`
    - `cp "C:\Program Files (x86)\sigc++\lib\sigc-3.0.lib %MY_LIB%\sigc-vc150-3_0.lib`
    - open the MSVC_Net2017\cairomm.sln file in Visual Studio
    - For all the project add `%MY_INC%` as additional include directory and `%MY_LIB%` as additional library directory
    - (or modify all the vcxproj files accordingly)
    - build the complete project folder

# Building MooViE
- Build freetype2
    - again a cmake project so:
    - `mkdir build` and `cd build`
    - `cmake -A Win32 ..`
    - `msbuild ALL_BUILD.vcxproj`
    - In the admin shell `msbuild INSTALL.vcxproj`





# Sources:
- https://www.cairographics.org/end_to_end_build_for_win32/
- https://stackoverflow.com/questions/32127524/how-to-install-and-use-make-in-windows