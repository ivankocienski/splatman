
#set(CMAKE_VERBOSE_MAKEFILE ON)

# our exe name
project (splatterman)

cmake_minimum_required (VERSION 2.6)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
#include_directories(${GLFW_INCLUDE_DIRS})

find_package (OpenGL REQUIRED)
find_package (PNG REQUIRED)

#find_package (Threads REQUIRED)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_SYSTEM ON)
find_package (Boost COMPONENTS thread system REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package (Portaudio REQUIRED)


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
  src/splash-screen.cc
  src/show-scores.cc
  src/score-board.cc
  src/new-high-score.cc
  src/sounds.cc

	src/audio/audio-exception.cc
	src/audio/audio-service.cc
	src/audio/audio-channel.cc
	src/audio/audio-pattern.cc
	src/audio/audio-oscillator-base.cc
	src/audio/audio-sine-oscillator.cc
	src/audio/audio-square-oscillator.cc
	src/audio/audio-noise-oscillator.cc
	src/audio/audio-saw-oscillator.cc
	src/audio/audio-triangle-oscillator.cc
)


link_libraries(
  #${PTHREAD_LIBRARY}
  ${Boost_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLFW_LIBRARIES}
  ${PNG_LIBRARY}
  ${ZLIB_LIBRARY}
  ${PORTAUDIO_LIBRARIES}
)

add_executable(splatterman ${SRC} )

add_custom_command(TARGET splatterman POST_BUILD 
  COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/data COMMENT "removing stale data
  directory"
  COMMAND ln -sf ${CMAKE_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data COMMENT "linking data directory"
)
