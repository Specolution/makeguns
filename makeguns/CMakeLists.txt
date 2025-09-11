# CMakeList.txt : CMake project for makeguns, include source and define
# project specific logic here.
#

# Add source to this project's executable.

find_package (SDL3 REQUIRED)
add_executable (makeguns "makeguns.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET makeguns PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(makeguns PRIVATE SDL3::SDL3)

# TODO: Add tests and install targets if needed.
