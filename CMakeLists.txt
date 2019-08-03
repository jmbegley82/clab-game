cmake_minimum_required (VERSION 2.6)
project (Clab-game)
set (Clab-game_VERSION_MAJOR 0)
set (Clab-game_VERSION_MINOR 5)
set (DEST_DIR "${CMAKE_INSTALL_PREFIX}")
set (prefix "${DEST_DIR}")
set (exec_prefix "${prefix}")
set (libdir "${prefix}/lib")
set (PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
set (PACKAGE_VERSION "${Clab-game_VERSION_MAJOR}.${Clab-game_VERSION_MINOR}")
set (API_VERSION "${Clab-game_VERSION_MAJOR}")
set (includedir "${prefix}/include")

configure_file(
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/src/config.h"
	)
configure_file(
	"${PROJECT_SOURCE_DIR}/Clab-game.pc.in"
	"${PROJECT_BINARY_DIR}/Clab-game-${API_VERSION}.pc"
	@ONLY
	)
configure_file(
	"${PROJECT_SOURCE_DIR}/src/Clab-game.h.in"
	"${PROJECT_BINARY_DIR}/src/Clab-game.h"
	@ONLY
	)
include_directories("${PROJECT_BINARY_DIR}/src;${PROJECT_SOURCE_DIR}/src/Atoms;${PROJECT_SOURCE_DIR}/src/System;${PROJECT_SOURCE_DIR}/src/Platform;${PROJECT_SOURCE_DIR}/src")

#include_directories (src)
find_package (PkgConfig REQUIRED)
pkg_check_modules(Clab REQUIRED Clab-0>=0.5)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_image REQUIRED SDL2_image)
pkg_check_modules(SDL2_mixer REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)

add_library(Clab-game SHARED src/Atoms/Video.cpp src/Atoms/Manager.cpp src/Clab-game.cpp)
set_target_properties(Clab-game PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}-${API_VERSION}"
					   VERSION "${PACKAGE_VERSION}"
					   SOVERSION "${Clab-game_VERSION_MAJOR}")
target_link_libraries(Clab-game ${Clab_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES} ${SDL2_mixer_LIBRARIES} ${SDL2_ttf_LIBRARIES})
target_include_directories(Clab-game PUBLIC ${Clab_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
target_compile_options(Clab-game PUBLIC ${SPECIAL_MCPU} ${SPECIAL_INCLUDES})
target_compile_definitions(Clab-game PUBLIC ${SPECIAL_DEFS} ${Clab_CFLAGS_OTHER} ${SDL2_CFLAGS_OTHER} ${SDL2_image_CFLAGS_OTHER} ${SDL2_mixer_CFLAGS_OTHER} ${SDL2_ttf_CFLAGS_OTHER})

add_executable(clabtest EXCLUDE_FROM_ALL src/Test/main.cpp)
target_link_libraries(clabtest Clab-game)
target_compile_options(clabtest PUBLIC ${SPECIAL_MCPU} ${SPECIAL_INCLUDES})
target_compile_definitions(clabtest PUBLIC ${SPECIAL_DEFS})

install(TARGETS Clab-game
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib)
install(FILES ${PROJECT_BINARY_DIR}/src/Clab-game.h src/Atoms/Video.h src/Atoms/Manager.h
	DESTINATION include/Clab-${API_VERSION})
install(FILES "${PROJECT_BINARY_DIR}/Clab-game-${API_VERSION}.pc"
	DESTINATION lib/pkgconfig)

set(CPACK_PACKAGE_VERSION ${PACKAGE_VERSION})
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "jmb")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "clab (>= 0.5), libsdl2-2.0-0, libsdl2-mixer-2.0-0, libsdl2-image-2.0-0, libsdl2-ttf-2.0-0")
include(CPack)
