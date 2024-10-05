cmake_minimum_required(VERSION 3.29)
project(game_cocos2d)

set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(game_cocos2d main.cpp)
target_link_libraries(game_cocos2d sfml-system sfml-window sfml-graphics)
