cmake_minimum_required(VERSION 3.8)
project(blacktrack)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

file(GLOB_RECURSE BLACKTRACK_SRC
    # BlackTrack
    "src/*.cpp"
    "src/*.c"
    "include/*.hpp"
    "include/*.h"
    "res/*.hpp"
    "res/*.h"
    
    # glad
    "lib/glad/src/*.c"
)

add_executable(blacktrack ${BLACKTRACK_SRC})
target_include_directories(blacktrack PUBLIC include include/ImGuiFileBrowser lib/glfw/include lib/glad/include lib/pugixml/src)
target_link_libraries(blacktrack PUBLIC imgui glfw glm pugixml)