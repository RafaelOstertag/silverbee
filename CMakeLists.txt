cmake_minimum_required(VERSION 3.10)

project(SilverBee VERSION 1.0.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -pedantic -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-g0 -O3 -Wall -pedantic -Werror -DNDEBUG")

include(FindPkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(GST REQUIRED gstreamer-1.0)

add_subdirectory(src)

install(TARGETS silverbee DESTINATION bin)
install(FILES data/sound/funkysynth.wav DESTINATION share/silverbee/sound)
install(FILES data/background/img1.jpg DESTINATION share/silverbee/background)

configure_file(silverbee.hh.in silverbee.hh)

