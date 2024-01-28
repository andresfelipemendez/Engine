set VCPKG_FEATURE_FLAGS=manifests
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/Users/andres/Development/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build