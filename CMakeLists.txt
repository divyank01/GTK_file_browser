cmake_minimum_required(VERSION 3.6)
project(GTKGUI)

set(CMAKE_CXX_STANDARD 11)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
find_package(Boost COMPONENTS system filesystem REQUIRED)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})
# Add an executable compiled from hello.c
# Link the target to the GTK+ libraries
set(SOURCE_FILES main.cpp welcome_page.cpp welcome_page.h app.h)
add_executable(GTKGUI ${SOURCE_FILES})

target_link_libraries(GTKGUI ${Boost_LIBRARIES} ${GTK3_LIBRARIES})