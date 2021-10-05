cmake_minimum_required (VERSION 3.8)

set(SFML_DIR "F:/SFML/x64/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5.1 COMPONENTS graphics system window REQUIRED)

# file (GLOB srcs CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB srcs CONFIGURE_DEPENDS "src/*.*")

add_executable (main ${srcs})

# target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(main sfml-graphics sfml-system sfml-window)

