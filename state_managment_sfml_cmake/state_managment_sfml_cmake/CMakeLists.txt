cmake_minimum_required (VERSION 3.8)

set(SFML_DIR "F:/SFML/x64/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5.1 COMPONENTS graphics system window REQUIRED)

# add_executable (main src/main.cpp lib/game.cpp lib/window.cpp lib/EventManager.cpp lib/StateManager.cpp lib/IntroState.cpp lib/MainMenuState.cpp)

file (GLOB libs CONFIGURE_DEPENDS "lib/*.cpp")
add_executable (main src/main.cpp ${libs})

target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(main sfml-graphics sfml-system sfml-window)


