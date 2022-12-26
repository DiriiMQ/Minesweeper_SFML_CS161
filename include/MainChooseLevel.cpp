//
// Created by dirii on 23/12/2022.
//

#include "MainWindow.h"

void Window::resetChooseLevel() {
    this->isCustomPressed = false;
    this->inputString = "";
    this->textInputWidth.setString(this->inputString);
    this->textInputHeight.setString(this->inputString);
    this->textInputMines.setString(this->inputString);
    this->currentInputType = INPUT_WIDTH;
    this->errorSizeText.setString("");
}

void Window::pollEventTextInput() {
    if (this->event.type == sf::Event::TextEntered) {
        if (this->event.text.unicode >= '0' && this->event.text.unicode <= '9') {
            if (this->event.text.unicode == '0' && this->inputString.empty())
                return;
            if (this->inputString.size() < 3)
                this->inputString += this->event.text.unicode;
        }
    } else if (this->event.type == sf::Event::KeyPressed) {
        if (this->event.key.code == sf::Keyboard::BackSpace) {
            if (this->inputString.size())
                this->inputString.pop_back();
        }
    }
}

void Window::pollEventChooseLevel() {
    this->moveOnAButton(this->buttonEasy, this->textureEasy);
    this->moveOnAButton(this->buttonMedium, this->textureMedium);
    this->moveOnAButton(this->buttonHard, this->textureHard);
    this->moveOnAButton(this->buttonPlay, this->texturePlay);
    this->moveOnAButton(this->buttonBack, this->textureBack);

    if (!this->isCustomPressed)
        this->moveOnAButton(this->buttonCustom, this->textureCustom);

    this->pollEventTextInput();

    // catch mouse event here
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->mouseHeld) {
            this->mouseHeld = true;
            if (this->isMovingOnButton(this->buttonEasy)) {
                this->nBoard = this->mBoard = 9;
                this->minesBoard = 10;
                this->currentLevel = EASY;
                this->initGame();

                this->resetChooseLevel();
                std::cout << "Pressed Easy\n";
                this->currentScreen = GAME;
            } else if (this->isMovingOnButton(this->buttonMedium)) {
                this->nBoard = this->mBoard = 16;
                this->minesBoard = 40;
                this->currentLevel = MEDIUM;
                this->initGame();

                this->resetChooseLevel();
                std::cout << "Pressed Medium\n";
                this->currentScreen = GAME;
            } else if (this->isMovingOnButton(this->buttonHard)) {
                this->nBoard = 16;
                this->mBoard = 30;
                this->minesBoard = 99;
                this->currentLevel = HARD;
                this->initGame();

                this->resetChooseLevel();
                std::cout << "Pressed Hard\n";
                this->currentScreen = GAME;
            } else if (this->isMovingOnButton(this->buttonCustom)) {
                if (!this->isCustomPressed) {
                    this->isCustomPressed = true;
                    std::cout << "Pressed Custom\n";
                }
            } else if (this->isMovingOnButton(this->buttonPlay)) {
                this->resetCursor();
                this->mBoard = std::stoi(this->textInputWidth.getString().isEmpty() ? std::string("0") : std::string(this->textInputWidth.getString()));
                this->nBoard = std::stoi(this->textInputHeight.getString().isEmpty() ? std::string("0") : std::string(this->textInputHeight.getString()));
                this->minesBoard = std::stoi(this->textInputMines.getString().isEmpty() ? std::string("0") : std::string(this->textInputMines.getString()));

                if (this->minesBoard == 0 or this->minesBoard >= this->nBoard * this->mBoard or this->nBoard > 28 or this->mBoard > 55) {
                    this->errorSizeText.setString("Width <= 55 | Height <= 28 | Mines <= Width * Height");
                    return;
                }

                this->currentLevel = -1;
                this->initGame();
                std::cout << "Custom valid " << this->nBoard << ' ' << this->mBoard << ' ' << this->minesBoard << '\n';

                this->resetChooseLevel();
                std::cout << "Pressed Play\n";
                this->currentScreen = GAME;
            } else if (this->isMovingOnButton(this->buttonBack)) {
                this->resetChooseLevel();
                this->currentScreen = MENU;
                std::cout << "Pressed Back\n";
            } else if (this->isMovingOnButton(this->textboxWidth)) {
                this->resetCursor();
                this->inputString = this->textInputWidth.getString();
                this->currentInputType = INPUT_WIDTH;
            } else if (this->isMovingOnButton(this->textboxHeight)) {
                this->resetCursor();
                this->inputString = this->textInputHeight.getString();
                this->currentInputType = INPUT_HEIGHT;
            } else if (this->isMovingOnButton(this->textboxMines)) {
                this->resetCursor();
                this->inputString = this->textInputMines.getString();
                this->currentInputType = INPUT_MINES;
            }
        }
    } else {
        this->mouseHeld = false;
    }
}

void Window::updateChooseLevel() {
    float diff2buttons = 40,
            xButton = this->window->getSize().x / 2.0 - this->buttonEasy.getTexture()->getSize().x / 2.0,
            yEasy = this->window->getSize().y / 2.0 - 3 * this->buttonEasy.getTexture()->getSize().y,
            yMedium = yEasy + (this->buttonEasy.getTexture()->getSize().y + diff2buttons) * 1,
            yHard = yEasy + (this->buttonEasy.getTexture()->getSize().y + diff2buttons) * 2,
            yCustom = yEasy + (this->buttonEasy.getTexture()->getSize().y + diff2buttons) * 3,
            yPlay = this->window->getSize().y - this->buttonPlay.getTexture()->getSize().y - diff2buttons,
            xBack = this->window->getSize().x - this->buttonBack.getTexture()->getSize().x - diff2buttons,
            yBack = yPlay,
            xError = this->window->getSize().x / 2.0 - this->errorSizeText.getLocalBounds().width / 2.0,
            yError = yPlay - diff2buttons;

    this->buttonEasy.setPosition(xButton, yEasy);
    this->buttonMedium.setPosition(xButton, yMedium);
    this->buttonHard.setPosition(xButton, yHard);
    this->buttonCustom.setPosition(xButton, yCustom);

    this->errorSizeText.setPosition(xError, yError);
    this->buttonPlay.setPosition(xButton, yPlay);

    this->buttonBack.setPosition(xBack, yBack);

    // display the input fields
    if (this->isCustomPressed) {
//        this->textInputWidth.setString("123");
//        this->textInputHeight.setString("123");
//        this->textInputMines.setString("123");
        float diff2lines = diff2buttons,
                xText = this->window->getSize().x / 16.0,
                xTextBox = xText + this->textHeight.getLocalBounds().width + diff2lines,
                yTextWidth = yEasy + (this->textboxWidth.getTexture()->getSize().y - this->textWidth.getLocalBounds().height) / 2.0,
                yTextHeight = yMedium + (this->textboxHeight.getTexture()->getSize().y - this->textHeight.getLocalBounds().height) / 2.0,
                yTextMines = yHard + (this->textboxMines.getTexture()->getSize().y - this->textMines.getLocalBounds().height) / 2.0,

                xTextInput = xTextBox + this->textureTextbox.getSize().y / 5,
                yTextInputWidth = yEasy + (this->textboxWidth.getTexture()->getSize().y - this->textInputWidth.getLocalBounds().height) / 3.0,
                yTextInputHeight = yMedium + (this->textboxHeight.getTexture()->getSize().y - this->textInputHeight.getLocalBounds().height) / 3.0,
                yTextInputMines = yHard + (this->textboxMines.getTexture()->getSize().y - this->textInputMines.getLocalBounds().height) / 3.0;

        this->textWidth.setPosition(xText, yTextWidth);
        this->textHeight.setPosition(xText, yTextHeight);
        this->textMines.setPosition(xText, yTextMines);

        this->textboxWidth.setPosition(xTextBox, yEasy);
        this->textboxHeight.setPosition(xTextBox, yMedium);
        this->textboxMines.setPosition(xTextBox, yHard);

        this->textInputWidth.setPosition(xTextInput, yTextInputWidth);
        this->textInputHeight.setPosition(xTextInput, yTextInputHeight);
        this->textInputMines.setPosition(xTextInput, yTextInputMines);

        // display cursor
        this->textEffectTime += clock.restart();

        if (this->textEffectTime >= sf::seconds(0.5f)) {
            this->showCursor = !this->showCursor;
            this->textEffectTime = sf::Time::Zero;
        }

        switch (this->currentInputType) {
            case INPUT_WIDTH:
                this->textInputWidth.setString(this->inputString + (this->showCursor ? "|": ""));
                break;
            case INPUT_HEIGHT:
                this->textInputHeight.setString(this->inputString + (this->showCursor ? "|": ""));
                break;
            case INPUT_MINES:
                this->textInputMines.setString(this->inputString + (this->showCursor ? "|": ""));
                break;
        }
    }
}

void Window::renderChooseLevel(sf::RenderTarget &target) {
    target.draw(this->buttonEasy);
    target.draw(this->buttonMedium);
    target.draw(this->buttonHard);
    target.draw(this->buttonCustom);

    if (this->isCustomPressed) {
        target.draw(this->errorSizeText);
        target.draw(this->buttonPlay);

        target.draw(this->textWidth);
        target.draw(this->textboxWidth);

        target.draw(this->textHeight);
        target.draw(this->textboxHeight);

        target.draw(this->textMines);
        target.draw(this->textboxMines);

        target.draw(this->textInputWidth);
        target.draw(this->textInputHeight);
        target.draw(this->textInputMines);
    }

    target.draw(this->buttonBack);
}
