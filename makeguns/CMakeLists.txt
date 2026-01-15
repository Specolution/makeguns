# CMakeList.txt : CMake project for makeguns, include source and define
# project specific logic here.
#

# Add source to this project's executable.

find_package (SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(glm REQUIRED)

add_executable (makeguns "makeguns.cpp" "timer.h" "animation.h" "timer.cpp" "animation.cpp" "gameobject.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET makeguns PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(makeguns PRIVATE SDL3::SDL3 SDL3_image::SDL3_image glm::glm)

# TODO: Add tests and install targets if needed.
