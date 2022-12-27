# CMakeLibTemplate
## just as a simple learning project which parts may be used in other projects

based on vcpkg package manager. Be sure to have all packages installed:
```bash
vcpkg install zlib
vcpkg install POCO 
vcpkg install fmt
vcpkg install spdlog
vcpkg install jsoncpp
vcpkg install boost
```

To integrate VCPKG add to build process:
-DCMAKE_TOOLCHAIN_FILE=${VCPKG_HOME}/scripts/buildsystems/vcpkg.cmake
