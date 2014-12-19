
# our exe name
project (splatterman)

cmake_minimum_required (VERSION 2.6)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
#include_directories(${GLFW_INCLUDE_DIRS})

find_package (OpenGL REQUIRED)
find_package (PNG REQUIRED)


# source files. sure, there's a better way of doing this
set (SRC
  src/application.cc
  src/main.cc
  src/actor.cc
  src/board.cc
  src/ghost.cc
  src/graphics.cc
  src/player.cc
  src/mode-base.cc
  src/round.cc
)


link_libraries(
  ${OPENGL_LIBRARIES}
  ${GLFW_LIBRARIES}
  ${PNG_LIBRARY}
  ${ZLIB_LIBRARY}
)

add_executable(splatterman ${SRC} )

add_custom_command(TARGET splatterman POST_BUILD 
  COMMAND ln -sf ${CMAKE_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data COMMENT "linking data directory"
)
