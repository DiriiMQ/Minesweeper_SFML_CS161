//
// Created by dirii on 23/12/2022.
//

#include "MainWindow.h"

void Window::resetScoreboard() {
    // nothing here
}

void Window::pollEventScoreBoard() {
    this->moveOnAButton(this->buttonBack, this->textureBack);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->mouseHeld) {
            this->mouseHeld = true;
            if (this->isMovingOnButton(this->buttonBack)) {
                this->resetScoreboard();
                this->currentScreen = MENU;
                std::cout << "Pressed Back\n";
            }
        }
    } else {
        this->mouseHeld = false;
    }
}

void Window::updateScoreBoard() {
    float diff2lines = 40,
            widthLevelFrame = 440,
            heightLevelFrame = 804,
            xBack = this->window->getSize().x - this->buttonBack.getTexture()->getSize().x - diff2lines,
            yBack = this->window->getSize().y - this->buttonBack.getTexture()->getSize().y - diff2lines / 3.0,
            xSCFrame = (this->window->getSize().x - this->scoreboardFrame.getTexture()->getSize().x) / 2.0,
            ySCFrame = -diff2lines / 1.5,
            xEasyFrameRaw = 14,
            xMediumFrameRaw = 536,
            xHardFrameRaw = 1058,
            yFrameRaw = 121,
            xLineEasy1 = xEasyFrameRaw + xSCFrame + diff2lines / 2.0,
            xLineEasy2 = xEasyFrameRaw + xSCFrame + widthLevelFrame - diff2lines * 1.8,
            yLineEasy = yFrameRaw + ySCFrame + diff2lines / 2.0,
            xLineMedium1 = xMediumFrameRaw + xSCFrame + diff2lines / 2.0,
            xLineMedium2 = xMediumFrameRaw + xSCFrame + widthLevelFrame - diff2lines * 1.8,
            yLineMedium = yLineEasy,
            xLineHard1 = xHardFrameRaw + xSCFrame + diff2lines / 2.0,
            xLineHard2 = xHardFrameRaw + xSCFrame + widthLevelFrame - diff2lines * 1.8,
            yLineHard = yLineEasy;

    this->yLimit = yFrameRaw + ySCFrame + heightLevelFrame - diff2lines;

    this->scoreboardFrame.setPosition(xSCFrame, ySCFrame);
    this->buttonBack.setPosition(xBack, yBack);

    // set tung thanh phan cho moi mode
    this->initTextScoreboard();

    for (auto &i : textRecordEasy) {
        i.first.setPosition(xLineEasy1, yLineEasy);
        i.second.setPosition(xLineEasy2, yLineEasy);
        yLineEasy += diff2lines;
    }

    for (auto &i : textRecordMedium) {
        i.first.setPosition(xLineMedium1, yLineMedium);
        i.second.setPosition(xLineMedium2, yLineMedium);
        yLineMedium += diff2lines;
    }

    for (auto &i : textRecordHard) {
        i.first.setPosition(xLineHard1, yLineHard);
        i.second.setPosition(xLineHard2, yLineHard);
        yLineHard += diff2lines;
    }
}

void Window::renderScoreBoard(sf::RenderTarget &target) {
    target.draw(this->scoreboardFrame);

    target.draw(this->buttonBack);

    for (auto i : this->textRecordEasy) {
        if (i.first.getPosition().y > this->yLimit)
            break;
        target.draw(i.first);
        target.draw(i.second);
    }

    for (auto i : this->textRecordMedium) {
        if (i.first.getPosition().y > this->yLimit)
            break;
        target.draw(i.first);
        target.draw(i.second);
    }

    for (auto i : this->textRecordHard) {
        if (i.first.getPosition().y > this->yLimit)
            break;
        target.draw(i.first);
        target.draw(i.second);
    }
}
