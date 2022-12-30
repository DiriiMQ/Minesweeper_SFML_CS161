set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

cmake_minimum_required(VERSION 3.24)
project(minesweeper_gui)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(minesweeper_gui ${CMAKE_SOURCE_DIR}/main.cpp ${CMAKE_SOURCE_DIR}/include/MainWindow.cpp ${CMAKE_SOURCE_DIR}/include/MainWindow.h ${CMAKE_SOURCE_DIR}/include/CoreMinesweeper.h ${CMAKE_SOURCE_DIR}/include/CoreMinesweeper.cpp ${CMAKE_SOURCE_DIR}/include/CustomRandom.cpp ${CMAKE_SOURCE_DIR}/include/CustomRandom.h ${CMAKE_SOURCE_DIR}/include/Ranking.cpp ${CMAKE_SOURCE_DIR}/include/Ranking.h ${CMAKE_SOURCE_DIR}/include/MainMenu.cpp ${CMAKE_SOURCE_DIR}/include/MainGame.cpp ${CMAKE_SOURCE_DIR}/include/MainChooseLevel.cpp ${CMAKE_SOURCE_DIR}/include/MainScoreboard.cpp)

target_link_libraries(minesweeper_gui sfml-graphics sfml-window sfml-system)