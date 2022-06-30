cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakeModules/")

project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3 REQUIRED)
find_package(SqliteOrm CONFIG REQUIRED)
find_package(GLM CONFIG REQUIRED)

find_path(TINYGLTF_INCLUDE_DIRS "tiny_gltf.h")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/stb ${CMAKE_CURRENT_SOURCE_DIR}/lib/tiny_obj_loader)
include_directories(${GLFW3_INCLUDE_DIRS} )

file(GLOB IMGUI_SRC
     "imgui/*.cpp"
) 

file(GLOB ENGINE_SRC
     "src/*.cpp"
)

add_executable(Engine ${ENGINE_SRC}  ${IMGUI_SRC} )

add_subdirectory(glad/)

target_include_directories(Engine PRIVATE ${TINYGLTF_INCLUDE_DIRS})
target_link_libraries(Engine glfw glad glm::glm sqlite_orm::sqlite_orm)

file(GLOB SHADERS
  "assets/shaders/*.glsl"
)
file(GLOB MODELS
  "assets/models/*.glb"
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
