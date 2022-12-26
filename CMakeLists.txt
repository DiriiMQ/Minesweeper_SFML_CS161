cmake_minimum_required(VERSION 3.24)
project(minesweeper_gui)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(minesweeper_gui main.cpp include/MainWindow.cpp include/MainWindow.h include/CoreMinesweeper.h include/CoreMinesweeper.cpp include/CustomRandom.cpp include/CustomRandom.h include/Ranking.cpp include/Ranking.h include/MainMenu.cpp include/MainGame.cpp include/MainChooseLevel.cpp include/MainScoreboard.cpp)

target_link_libraries(minesweeper_gui sfml-graphics sfml-window sfml-system)