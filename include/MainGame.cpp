//
// Created by dirii on 23/12/2022.
//

#include "MainWindow.h"

int Window::initGameFromLocal() {
    int totalSeconds;

    this->ms = new MineSweeper();

    if (this->ms->load_from_file(totalSeconds, this->currentLevel) == _FILE_NOT_FOUND)
        return _FILE_NOT_FOUND;
    std::cout << "Loaded from the local file!\n";
//    this->printBoard();

    this->nBoard = this->ms->get_row();
    this->mBoard = this->ms->get_column();
    this->cellHasNoMine = this->ms->initial_no_mine();
    this->curX = this->cellHasNoMine.first;
    this->curY = this->cellHasNoMine.second;
    this->status = this->ms->get_initial_state();
    this->updatedScore = (this->status ? true : false);
    this->alive = true;
    this->clockRunningGame.restart();
    this->runningTime = sf::seconds(totalSeconds);
    this->gameTimerText.setString("00:00");
    this->gameRemainingMinesText.setString(std::to_string(this->ms->get_remaining_mines()));
    this->originX = this->window->getSize().x / 2.0 - this->sideCell * this->mBoard / 2.0;
    this->originY = 3 * this->sideCell;
    this->gameBoard.resize(this->nBoard, std::vector<sf::Sprite>(this->mBoard));

    std::cout << "gameBoard after resized: " << this->gameBoard.size() << '\n';

    return _OK;
}

void Window::initGame() {
    this->ms = new MineSweeper(this->nBoard, this->mBoard, this->minesBoard);
    this->ms->generate_board(true);
    this->cellHasNoMine = this->ms->initial_no_mine();
    this->curX = this->cellHasNoMine.first;
    this->curY = this->cellHasNoMine.second;
    this->status = this->ms->get_initial_state();
    this->updatedScore = false;
    this->alive = true;
    this->clockRunningGame.restart();
    this->runningTime = sf::Time::Zero;
    this->gameTimerText.setString("00:00");
    this->gameRemainingMinesText.setString(std::to_string(this->ms->get_remaining_mines()));
    this->originX = this->window->getSize().x / 2.0 - this->sideCell * this->mBoard / 2.0;
    this->originY = 3 * this->sideCell;
    this->gameBoard.resize(this->nBoard, std::vector<sf::Sprite>(this->mBoard));
    std::cout << "Configuration of game " << this->nBoard << ' ' << this->mBoard << ' ' << this->minesBoard << '\n';
//    this->printBoard(); // for testing
}

void Window::quitGame() {
    /**
     * when quit signal is detected, then check if alive == true then save the current game*/

    if (this->alive) {
        // save game here
        this->ms->save_file(this->runningTime.asSeconds(), this->currentLevel);
        delete ms;
        this->gameBoard.clear();
        this->alive = false;
        this->currentScreen = MENU;
        this->currentLevel = -1;
        std::cout << "Deleted\n";
    }
}

void Window::pollEventGame() {
//    std::cout << "still okk\n";
    this->moveOnAButton(this->buttonBack, this->textureBack);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->mouseHeld) {
            this->mouseHeld = true;
            if (this->isMovingOnButton(this->buttonBack)) {
                this->currentScreen = MENU;
                this->quitGame();
            } else if (this->status == _OK) {
                for (int i = 0; i < this->nBoard; ++i) {
                    for (int j = 0; j < this->mBoard; ++j) {
                        if (this->isMovingOnButton(this->gameBoard[i][j])) {
                            this->status = this->ms->choose(i, j, _OPEN_A_CELL, false);
                        }
                    }
                }
            }
        }
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (!this->mouseHeld) {
            this->mouseHeld = true;
            if (this->status == _OK) {
                for (int i = 0; i < this->nBoard; ++i) {
                    for (int j = 0; j < this->mBoard; ++j) {
                        if (this->isMovingOnButton(this->gameBoard[i][j])) {
                            if (this->ms->get_state_cell(i, j) != _SET_FLAG)
                                this->status = this->ms->choose(i, j, _SET_FLAG, false);
                            else
                                this->status = this->ms->choose(i, j, _REMOVE_FLAG, false);
                        }
                    }
                }
            }
        }
    } else {
        this->mouseHeld = false;
    }
}

void Window::updateGame() {
    float diff2lines = 20,
            yInfo = diff2lines,
            xRemainingFlag = diff2lines * 2,
            xBack = this->window->getSize().x - this->buttonBack.getTexture()->getSize().x - diff2lines * 2,
            xTimer = this->window->getSize().x / 2.0 - this->gameTimerText.getLocalBounds().width / 2.0,
            xResult = (xRemainingFlag + xTimer) / 2.0 - this->textLose.getLocalBounds().width;

    // if user wins game
    if (this->status) {
        if (!this->updatedScore && this->status == _WIN && this->currentLevel != -1) {
            this->ranking.saveRecord(this->currentLevel, this->runningTime.asSeconds());
            this->updatedScore = true;
        }
    }

    this->textWin.setPosition(xResult, yInfo);
    this->textLose.setPosition(xResult, yInfo);

    this->gameRemainingMinesText.setString(std::to_string(this->ms->get_remaining_mines()));

    this->gameRemainingMinesText.setPosition(xRemainingFlag, yInfo);
    this->gameTimerText.setPosition(xTimer, yInfo);
    this->buttonBack.setPosition(xBack, yInfo);

    if (this->status == _OK)
        this->runningTime += clockRunningGame.restart();
    this->gameTimerText.setString(this->secondsToString(this->runningTime));

//    std::cout << "The height is " << yInfo + diff2lines << '\n';
    std::vector<std::vector<int>> data = this->ms->get_board();
    std::vector<std::vector<int>> state = this->ms->get_state();

//    std::cout << "still ok \n";

    // print the game board
//    std::cout << "Size of the vector gameBoard " << this->gameBoard.size() << ' ' << this->gameBoard[0].size() << '\n';
    for (int i = 0; i < this->nBoard; ++i) {
        for (int j = 0; j < this->mBoard; ++j) {
            sf::Sprite &currentCell = this->gameBoard[i][j];
            currentCell.setPosition(this->originX + j * this->sideCell, this->originY + i * this->sideCell);
            currentCell.setTexture(this->textureGameObjects);

            switch (state[i][j]) {
                case _ORIGINAL:
                    currentCell.setTextureRect(sf::IntRect(10 * this->sideCell, 0, this->sideCell, this->sideCell));
                    break;
                case _OPEN_A_CELL:
                    if (data[i][j] > -1)
                        currentCell.setTextureRect(sf::IntRect(data[i][j] * this->sideCell, 0, this->sideCell, this->sideCell));
                    else
                        currentCell.setTextureRect(sf::IntRect(9 * this->sideCell, 0, this->sideCell, this->sideCell));
                    break;
                case _SET_FLAG:
                    currentCell.setTextureRect(sf::IntRect(11 * this->sideCell, 0, this->sideCell, this->sideCell));
                    break;
            }
        }
    }

//    std::cout << "still ok " << this->gameBoard.size() << '\n';// << ' ' << this->gameBoard[this->curX][this->curY].getPosition().y << '\n';
//    if (this->curX != -1 && this->curY != -1)
    this->flowerIcon.setPosition(this->gameBoard[this->curX][this->curY].getPosition());
}

void Window::renderGame(sf::RenderTarget &target) {
    target.draw(this->gameRemainingMinesText);
    target.draw(this->gameTimerText);
    target.draw(this->buttonBack);

    for (auto lines : this->gameBoard) {
        for (auto cell : lines)
            target.draw(cell);
    }

    switch (this->status) {
        case _WIN:
            target.draw(this->textWin);
            break;
        case _LOSE:
            target.draw(this->textLose);
            break;
    }

    if (!this->ms->isPlayed()) {
        target.draw(this->flowerIcon);
    }
}
