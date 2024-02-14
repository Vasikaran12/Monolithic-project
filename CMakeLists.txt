cmake_minimum_required(VERSION 3.5)
project(GTKTutorial)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(GTK3_INCLUDE_DIRS "C:/msys64/mingw64/include/")
set(GTK3_LIBRARY_DIRS "C:/msys64/mingw64/lib")
set(ENV{PKG_CONFIG_PATH} "C:/msys64/mingw64/lib/pkgconfig")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(SQLite3 REQUIRED sqlite3)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(TceLib main.c)
set_target_properties(TceLib PROPERTIES WIN32_EXECUTABLE true)
target_link_libraries(TceLib ${GTK3_LIBRARIES})
target_link_libraries(TceLib ${SQLite3_LIBRARIES})