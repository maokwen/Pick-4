# Prerequisites

The Project using [Vcpkg](https://github.com/microsoft/vcpkg) to build. Following the steps in [Readme](https://github.com/microsoft/vcpkg/blob/master/README.md) to build and install vcpkg. Then install packages and hook up user-wide integration:

```sh
vcpkg install sdl2 lua sol2
vcpkg integrate install
```

Now you can use Visual Studio open the project or build manually using cmake toolchain provide by vcpkg:

```sh
cd Pick-4
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]\scripts\buildsystems\vcpkg.cmake
make
```
