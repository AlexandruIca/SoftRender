[![Build Status](https://dev.azure.com/alexandruica703/SoftRender/_apis/build/status/AlexandruIca.SoftRender?branchName=master)](https://dev.azure.com/alexandruica703/SoftRender/_build/latest?definitionId=7&branchName=master)
[![Build Status](https://travis-ci.org/AlexandruIca/SoftRender.svg?branch=master)](https://travis-ci.org/AlexandruIca/SoftRender)
[![Build status](https://ci.appveyor.com/api/projects/status/vg0dynfq737bbow6?svg=true)](https://ci.appveyor.com/project/AlexandruIca/softrender)
[![codecov](https://codecov.io/gh/AlexandruIca/SoftRender/branch/master/graph/badge.svg)](https://codecov.io/gh/AlexandruIca/SoftRender)
------
# Basic library for practising computer graphics.

The single purpose of this library is to allow me to make a basic software
renderer to learn more about graphics programming.

You can check the documentation [here](https://alexandruica.github.io/SoftRender/)
though you won't see too much right now since the project is very young.

Check out the [examples](examples/) directory to see the library in use.

# Building

## Windows & GNU/Linux

First get [vcpkg](https://github.com/microsoft/vcpkg) and then install sdl2:
```sh
$ ./vcpkg install sdl2
```

Then use CMake to build the library(choose what you want to turn ON/OFF):
```sh
$ mkdir build && cd build

$ cmake -DSOFTRENDER_BUILD_TESTS=ON \
        -DSOFTRENDER_BUILD_EXAMPLES=ON \
        -DSOFTRENDER_BUILD_DOCS=OFF \
        -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake ..

$ cmake --build .
```

## MacOS

If you can't install vcpkg on a Mac you can easily build this without it:
```sh
$ brew install sdl2

$ mkdir build && cd build

$ cmake -DSOFTRENDER_BUILD_TESTS=ON \
        -DSOFTRENDER_BUILD_EXAMPLES=ON \
        -DSOFTRENDER_BUILD_DOCS=OFF ..

$ cmake --build .
```
