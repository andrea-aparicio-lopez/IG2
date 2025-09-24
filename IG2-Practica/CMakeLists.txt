cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
find_package(SDL2 REQUIRED)


# add the source files as usual
add_executable(TestApp src/Main.cpp src/IG2App.cpp)

#headers
include_directories(TestApp include)

# this also sets the includes and pulls third party dependencies
target_link_libraries(TestApp OgreMain OgreBites SDL2::SDL2 SDL2::SDL2main)
#include_directories(PUBLIC (OGRE_CV_INCLUDE_DIRS))

set_target_properties(TestApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
)

