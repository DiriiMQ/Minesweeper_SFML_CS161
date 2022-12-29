//
// Created by dirii on 19/12/2022.
//

#ifndef SFML_TEST_COREMINESWEEPER_H
#define SFML_TEST_COREMINESWEEPER_H

//#pragma once

#include <vector>
#include <utility>
#include <fstream>
#include <queue>
#include "CustomRandom.h"

namespace custom_constant{
    const int DX[] = {-1, -1, -1, 0, 0, 1, 1, 1},
            DY[] = {-1, 0, 1, -1, 1, -1, 0, 1};
}

#define _DATA_FILE "../static/game.dat"
#define _FILE_NOT_FOUND -1

#define _ORIGINAL 0
#define _OPEN_A_CELL 1
#define _SET_FLAG 2
#define _REMOVE_FLAG 3

#define _OK 0
#define _WIN 1
#define _LOSE 2

class MineSweeper_board{
protected:
    int row,
        column,
        number_mines;
    std::vector<std::vector<int>> board;

public:
    // initial
    void random_mines();
    void generate_board(bool isRandMines);
    void assign_board(std::vector<std::vector<int>> _board);
    std::vector<std::vector<int>> get_board();
    int get_row();
    int get_column();
};

class MineSweeper: public MineSweeper_board{
private:
    std::vector<std::vector<int>> game_state;

public:
    MineSweeper();
    MineSweeper(int row, int column, int number_mines);
    int choose(int i, int j, int option, bool isRec);
    std::vector<std::vector<int>> get_state();
    int get_state_cell(int i, int j);
    int get_remaining_mines();
    void save_file(int current_ticker, int current_level);
    int load_from_file(int &current_ticker, int &current_level);
    int get_initial_state();
    void assign_game_state(std::vector<std::vector<int>> _game_state);
    std::pair<int, int> initial_no_mine();
    bool isPlayed();
};

#endif //SFML_TEST_COREMINESWEEPER_H
