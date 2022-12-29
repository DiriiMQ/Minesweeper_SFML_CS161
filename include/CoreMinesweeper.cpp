//
// Created by dirii on 19/12/2022.
//

#include "CoreMinesweeper.h"

MineSweeper::MineSweeper() {
    int row = 10, column = 10, number_mines = 5;
    this->row = row;
    this->column = column;
    this->number_mines = number_mines;
    this->board.resize(row, std::vector<int>(column, 0));
    this->game_state.resize(row, std::vector<int>(column, 0));
}

MineSweeper::MineSweeper(int row, int column, int number_mines){
    this->row = row;
    this->column = column;
    this->number_mines = number_mines;
    this->board.resize(row, std::vector<int>(column, 0));
    this->game_state.resize(row, std::vector<int>(column, 0));
}

void MineSweeper_board::random_mines(){
    std::vector<bool> mine_state(this->row * this->column);
    for (int i = 0; i < this->number_mines; ++i) {
        mine_state[i] = 1;
    }

    rd::randomArray(mine_state);
    for (int i = 0; i < this->row * this->column; ++i) {
        this->board[i / this->column][i % this->column] = (mine_state[i] ? -1 : 0);
    }
}

void MineSweeper_board::generate_board(bool isRandMines = 1){
    if(isRandMines)
        this->random_mines();

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j) {
            if (this->board[i][j] == 0) {
                for (int u = 0; u < 8; ++u){
                    int new_i = i + custom_constant::DX[u],
                            new_j = j + custom_constant::DY[u];

                    if (new_i < 0 || new_i >= row || new_j < 0 || new_j >= column)
                        continue;

                    if (this->board[new_i][new_j] == -1)
                        ++this->board[i][j];
                }
            }
        }
}

std::vector<std::vector<int>> MineSweeper_board::get_board(){
    return this->board;
}

void MineSweeper_board::assign_board(std::vector<std::vector<int>> _board){
    this->board = _board;
}

int MineSweeper_board::get_row(){
    return this->row;
}

int MineSweeper_board::get_column(){
    return this->column;
}

int MineSweeper::choose(int chosen_i, int chosen_j, int option, bool isRec = 0){
    if (this->game_state[chosen_i][chosen_j] == _OPEN_A_CELL) {
        if (option == _OPEN_A_CELL) {
            int counter_flags = 0;
            for (int u = 0; u < 8; ++u) {
                int new_i = chosen_i + custom_constant::DX[u],
                        new_j = chosen_j + custom_constant::DY[u];

                if (new_i < 0 || new_i >= row || new_j < 0 || new_j >= column)
                    continue;

                if (this->game_state[new_i][new_j] == _SET_FLAG)
                    ++counter_flags;
            }
            if (counter_flags == this->board[chosen_i][chosen_j]){
                for (int u = 0; u < 8; ++u) {
                    int new_i = chosen_i + custom_constant::DX[u],
                            new_j = chosen_j + custom_constant::DY[u];

                    if (new_i < 0 || new_i >= row || new_j < 0 || new_j >= column)
                        continue;

                    int state = _OK;
                    if (this->game_state[new_i][new_j] == _OK)
                        state = this->choose(new_i, new_j, _OPEN_A_CELL);
                    if (state == _WIN)
                        return _WIN;
                    if (state == _LOSE)
                        return _LOSE;
                }
            }
        }
        return _OK;
    }
    switch (option) {
        case _OPEN_A_CELL:
            this->game_state[chosen_i][chosen_j] = _OPEN_A_CELL;
            if (this->board[chosen_i][chosen_j] == -1){
                for (int i = 0; i < row; ++i)
                    for (int j = 0; j < column; ++j)
                        this->game_state[i][j] = _OPEN_A_CELL;
                return _LOSE;
            }
            if (this->board[chosen_i][chosen_j] == _ORIGINAL) {
                for (int u = 0; u < 8; ++u) {
                    int new_i = chosen_i + custom_constant::DX[u],
                            new_j = chosen_j + custom_constant::DY[u];
                    if (new_i < 0 || new_i >= row || new_j < 0 || new_j >= column)
                        continue;

                    if (this->board[new_i][new_j] == _ORIGINAL && this->game_state[new_i][new_j] == _ORIGINAL) {
                        this->choose(new_i, new_j, _OPEN_A_CELL, 1);
                    }

                    if(this->board[chosen_i][chosen_j] == _ORIGINAL)
                        this->game_state[new_i][new_j] = _OPEN_A_CELL;
                }
            }
            break;

        case _SET_FLAG:
            this->game_state[chosen_i][chosen_j] = _SET_FLAG;
            break;

        case _REMOVE_FLAG:
            this->game_state[chosen_i][chosen_j] = _ORIGINAL;
            break;
    }

    if (isRec)
        return _OK;

    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j)
            if (this->board[i][j] != -1 && this->game_state[i][j] != _OPEN_A_CELL)
                return _OK;

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
            if (this->game_state[i][j] == _ORIGINAL)
                this->game_state[i][j] = _SET_FLAG;
    return _WIN;
}

std::vector<std::vector<int>> MineSweeper::get_state(){
    return this->game_state;
}

int MineSweeper::get_remaining_mines(){
    int counter_flag = 0;

    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j)
            if (this->game_state[i][j] == _SET_FLAG)
                ++counter_flag;

    return this->number_mines - counter_flag;
}

void MineSweeper::save_file(int current_ticker, int current_level){
    std::ofstream cout_file(_DATA_FILE);

    cout_file << current_ticker << ' ' << current_level << '\n';
    cout_file << this->row << ' ' << this->column << ' ' << this->number_mines << "\n\n";

    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j)
            cout_file << this->board[i][j] << " \n"[j == this->column - 1];

    cout_file << "\n";
    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j)
            cout_file << this->game_state[i][j] << " \n"[j == this->column - 1];
}

void MineSweeper::assign_game_state(std::vector<std::vector<int>> _game_state){
    this->game_state = _game_state;
}

int MineSweeper::load_from_file(int &current_ticker, int &current_level){
    std::ifstream cin_file(_DATA_FILE);
    if(!cin_file.good())
        return _FILE_NOT_FOUND;

    cin_file >> current_ticker >> current_level;
    cin_file >> this->row >> this->column >> this->number_mines;
    std::vector<std::vector<int>> _board(this->row, std::vector<int>(this->column));
    std::vector<std::vector<int>> _game_state(this->row, std::vector<int>(this->column));

    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j)
            cin_file >> _board[i][j];

    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j)
            cin_file >> _game_state[i][j];

    cin_file.close();

    this->assign_board(_board);
    this->assign_game_state(_game_state);
    return _OK;
}

int MineSweeper::get_initial_state(){
    bool win = false;

    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j)
            if (this->game_state[i][j] == _OK)
                return _OK;
            else if (this->game_state[i][j] == _SET_FLAG)
                win = true;

    return (win ? _WIN : _LOSE);
}

std::pair<int, int> MineSweeper::initial_no_mine(){
    bool full_ok = 1;
    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j)
            if (this->game_state[i][j] != _OK)
                full_ok = 0;

    if(!full_ok) return std::make_pair(0, 0);

    int cntMax = 0;
    std::pair<int, int> res = {-1, -1};
    std::vector<std::vector<bool>> visited(this->row, std::vector<bool>(this->column, false));
    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j) {
//            if (this->board[i][j] == _OK)
//                return std::make_pair(i, j);
            if (visited[i][j])
                continue;

            // find the cell in the region of the largest number of zeros
            if (this->board[i][j] == _OK) {
                int cnt = 1;
                std::queue<std::pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = true;
                while (q.size()) {
                    int x = q.front().first, y = q.front().second;
                    q.pop();
                    for (int ix = 0; ix < 8; ++ix) {
                        int nx = x + custom_constant::DX[ix], ny = y + custom_constant::DY[ix];

                        if (nx < 0 || ny < 0 || nx >= this->row || ny >= this->column || visited[nx][ny] || this->board[nx][ny] != _OK)
                            continue;

                        ++cnt;
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }

                if (cnt > cntMax) {
                    cntMax = cnt;
                    res = {i, j};
                }
            }
        }

    if (res.first != -1)
        return res;

    for (int i = 0; i < this->row; ++i)
        for (int j = 0; j < this->column; ++j)
            if (this->board[i][j] != -1)
                return std::make_pair(i, j);

    return std::make_pair(0, 0);
}

int MineSweeper::get_state_cell(int i, int j) {
    return this->game_state[i][j];
}

bool MineSweeper::isPlayed() {
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0;  j < this->column; ++j)
            if (this->game_state[i][j] != _OK)
                return true;
    }
    return false;
}
