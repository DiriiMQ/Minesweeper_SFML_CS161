//
// Created by dirii on 23/12/2022.
//

#include "MainWindow.h"

void Window::pollEventMenu() {
    this->moveOnAButton(this->buttonContinue, this->textureContinue);
    this->moveOnAButton(this->buttonNewGame, this->textureNewGame);
    this->moveOnAButton(this->buttonScoreBoard, this->textureScoreBoard);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->mouseHeld) {
            this->mouseHeld = true;
            if (this->isMovingOnButton(this->buttonNewGame)) {
                this->currentScreen = CHOOSE_LEVEL;
            } else if (this->isMovingOnButton(this->buttonContinue)) {
                /* check if the local data exists */
                if (this->initGameFromLocal() == _FILE_NOT_FOUND)
                    return;

                // show notification for _FILE_NOT_FOUND
                this->currentScreen = GAME;
            } else if (this->isMovingOnButton(this->buttonScoreBoard)) {
                this->currentScreen = SCORE_BOARD;
                this->ranking.reInit();
            }
        }
    } else {
        this->mouseHeld = false;
    }
}

void Window::updateMenu() {
    float diff2Button = 40,
            xButton = this->window->getSize().x / 2.0 - this->buttonNewGame.getTexture()->getSize().x / 2.0,
            yNewGame = this->window->getSize().y / 2.0 + this->buttonNewGame.getTexture()->getSize().y * 0,
            yContinue = yNewGame - this->buttonNewGame.getTexture()->getSize().y - diff2Button,
            yScoreBoard = yNewGame + this->buttonNewGame.getTexture()->getSize().y + diff2Button;

    this->buttonContinue.setPosition(xButton, yContinue);
    this->buttonNewGame.setPosition(xButton, yNewGame);
    this->buttonScoreBoard.setPosition(xButton, yScoreBoard);
}

void Window::renderMenu(sf::RenderTarget &target) {
    target.draw(this->buttonContinue);
    target.draw(this->buttonNewGame);
    target.draw(this->buttonScoreBoard);
}
