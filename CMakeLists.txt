cmake_minimum_required(VERSION 3.10)

project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3 3.3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW_INCLUDE_DIR}")

find_package(Vulkan REQUIRED)
message(STATUS "Found Vulkan in ${Vulkan_LIBRARIES}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/stb ${CMAKE_CURRENT_SOURCE_DIR}/lib/tiny_obj_loader)
include_directories(${GLFW3_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIRS})

add_executable(Engine src/main.cpp)

target_link_libraries(Engine glfw ${Vulkan_LIBRARIES})

file(GLOB SHADERS
  "assets/shaders/*.spv"
)
file(GLOB MODELS
  "assets/models/*.obj"
)

function (CopyFile ORIGINAL_TARGET FILE_PATH COPY_OUTPUT_DIRECTORY)
    # Copy to the disk at build time so that when the header file changes, it is detected by the build system.
    set(input ${FILE_PATH})
    get_filename_component(file_name ${FILE_PATH} NAME)
    set(output ${COPY_OUTPUT_DIRECTORY}/${file_name})
    set(copyTarget ${ORIGINAL_TARGET}-${file_name})

    add_custom_target(${copyTarget} DEPENDS ${output})
    add_dependencies(${ORIGINAL_TARGET} ${copyTarget})
    add_custom_command(
            DEPENDS ${input}
            OUTPUT ${output}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${input} ${output}
            COMMENT "Copying file to ${output}."
    )
endfunction ()

foreach(SHADER IN LISTS SHADERS)
    CopyFile(Engine ${SHADER} shaders)
endforeach()

foreach(MODEL IN LISTS MODELS)
    CopyFile(Engine ${MODEL} models)
endforeach()