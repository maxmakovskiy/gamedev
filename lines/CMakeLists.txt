cmake_minimum_required(VERSION 3.16)

project(lines LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# shared lib
find_package(SFML 2.5.1 COMPONENTS graphics system window REQUIRED)

add_executable(main
    src/main.cpp
    src/game.cpp
    src/window.cpp
)

target_link_libraries(main
    sfml-graphics
    sfml-system
    sfml-window
)
