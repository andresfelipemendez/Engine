# Engine

Project to implement what I've learned from reading:
 - [Real Time Rendering](https://www.realtimerendering.com/)
  
The goal is to implement multiple rendering API's in the list is:
 - OpenGL <- WIP
 - Vulkan [TODO]
 - Direct3D [TODO]
 - Metal [TODO]

I've implemented versions of the previous API in other projects, but not multiples in the same app.
- [Vulkan](https://github.com/andresfelipemendez/VulkanTesting)
- [Direct3D](https://github.com/andresfelipemendez/DODE)

install cmake
install vcpkg
https://vcpkg.io/en/getting-started

run vcpkg to install dependencies before the first time you run cmake

```
vcpkg install
```

```
cmake .. -DCMAKE_TOOLCHAIN_FILE="C:/Users/fmend/vcpkg/scripts/buildsystems/vcpkg.cmake" -G "Visual Studio 17"
```
 ```
entt:x64-windows                                   3.10.1#1         Gaming meets modern C++ - a fast and reliable en...
entt:x86-windows                                   3.10.1#1         Gaming meets modern C++ - a fast and reliable en...
glfw3:x64-windows                                  3.3.7            GLFW is a free, Open Source, multi-platform libr...
glfw3:x86-windows                                  3.3.7            GLFW is a free, Open Source, multi-platform libr...
glm:x64-windows                                    0.9.9.8#1        OpenGL Mathematics (GLM)
imgui:x64-windows                                  1.88             Bloat-free Immediate Mode Graphical User interfa...
imgui[dx12-binding]:x64-windows                                     Make available DirectX12 binding
imgui[glfw-binding]:x64-windows                                     Make available GLFW binding
imgui[opengl3-binding]:x64-windows                                  Make available OpenGL3/ES/ES2 (modern) binding
imgui[win32-binding]:x64-windows                                    Make available Win32 binding
nlohmann-json:x64-windows                          3.10.5#3         JSON for Modern C++
sqlite-orm:x64-windows                             1.7.1            SQLite ORM light header only library for modern C++
sqlite3:x64-windows                                3.37.2#1         SQLite is a software library that implements a s...
stb:x64-windows                                    2021-09-10       public domain header-only libraries
tinygltf:x64-windows                               2.5.0            A header only C++11 glTF 2.0 library.
vcpkg-cmake-config:x64-windows                     2022-02-06#1
vcpkg-cmake:x64-windows                            2022-06-07
```

### todo:
- [x] load models
- [ ] multiple materials/shaders
- [ ] vulkan IMGUI integration
- [ ] Animation
 