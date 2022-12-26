//
// Created by dirii on 09/12/2022.
//

#ifndef SFML_TEST_MAINWINDOW_H
#define SFML_TEST_MAINWINDOW_H

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "CoreMinesweeper.h"
#include "Ranking.h"

#define MENU 1
#define GAME 2
#define SCORE_BOARD 3
#define CHOOSE_LEVEL 4

#define INPUT_WIDTH 1
#define INPUT_HEIGHT 2
#define INPUT_MINES 3

#define DATA_FILE "../static/game.dat"

class Window{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;

    // mouse position
    sf::Vector2i mousePos;
    sf::Vector2f mousePosView;

    // game textures
    std::pair<sf::Texture, sf::Texture> textureContinue;
    std::pair<sf::Texture, sf::Texture> textureNewGame;
    std::pair<sf::Texture, sf::Texture> textureScoreBoard;

    std::pair<sf::Texture, sf::Texture> textureEasy;
    std::pair<sf::Texture, sf::Texture> textureMedium;
    std::pair<sf::Texture, sf::Texture> textureHard;
    std::pair<sf::Texture, sf::Texture> textureCustom;
    std::pair<sf::Texture, sf::Texture> texturePlay;

    std::pair<sf::Texture, sf::Texture> textureBack;

    sf::Texture textureTextbox;
    sf::Texture textureGameObjects;
    sf::Texture textureFlower;

    sf::Texture textureScoreboardFrame;


    // game sprites
    sf::Sprite buttonContinue;
    sf::Sprite buttonNewGame;
    sf::Sprite buttonScoreBoard;

    sf::Sprite buttonEasy;
    sf::Sprite buttonMedium;
    sf::Sprite buttonHard;
    sf::Sprite buttonCustom;
    sf::Sprite buttonPlay;

    sf::Sprite buttonBack;

    sf::Sprite textboxWidth;
    sf::Sprite textboxHeight;
    sf::Sprite textboxMines;

    sf::Sprite flowerIcon;

    std::vector<std::vector<sf::Sprite>> gameBoard;

    sf::Sprite scoreboardFrame;


    // game text
    std::string inputString;
    sf::Font font;

    sf::Text textWidth;
    sf::Text textHeight;
    sf::Text textMines;
    sf::Text errorSizeText;

    sf::Text textInputWidth;
    sf::Text textInputHeight;
    sf::Text textInputMines;

    sf::Text gameTimerText;
    sf::Text gameRemainingMinesText;

    sf::Text textWin;
    sf::Text textLose;

    std::vector<std::pair<sf::Text, sf::Text>> textRecordEasy;
    std::vector<std::pair<sf::Text, sf::Text>> textRecordMedium;
    std::vector<std::pair<sf::Text, sf::Text>> textRecordHard;

    // info scoreboard
    sf::RectangleShape firstLine, secondLine; // vertical line
    float yLimit;

    // clock for showing a cursor
    sf::Clock clock;
    sf::Time textEffectTime;
    bool showCursor;

    // game logics
    int currentScreen;
    bool mouseHeld;
    bool isCustomPressed;
    int currentInputType; // use in chooseLevel

    // info game
    int nBoard, mBoard, minesBoard, sideCell;
    MineSweeper *ms;
    std::pair<int, int> cellHasNoMine;
    int curX, curY, status, originX, originY;
    bool updatedScore, alive;
    sf::Clock clockRunningGame;
    sf::Time runningTime;
    Ranking ranking;
    int currentLevel;

    // private funcs
    void initVar();
    void initNewWindow();
    void initTextures();
    void initSprites();
    void initTexts();
    void initTextScoreboard();
    void initGame();
    int initGameFromLocal();

public:
    Window();
    ~Window();

    const bool running() const;

    // for testing
    void printBoard();

    void quitGame();

    void resetChooseLevel();
    std::string removeLastCursor(std::string n);
    void resetCursor();
    void resetScoreboard();

    bool isMovingOnButton(sf::Sprite& button);
    void moveOnAButton(sf::Sprite& button, std::pair<sf::Texture, sf::Texture>& texture);
    std::string secondsToString(sf::Time t);

    void pollEventMenu();
    void pollEventGame();
    void pollEventScoreBoard();
    void pollEventTextInput();
    void pollEventChooseLevel();
    void pollEvent();

    void updateMousePosition();
    void updateMenu();
    void updateGame();
    void updateScoreBoard();
    void updateChooseLevel();
    void update();

    void renderMenu(sf::RenderTarget& target);
    void renderGame(sf::RenderTarget& target);
    void renderScoreBoard(sf::RenderTarget& target);
    void renderChooseLevel(sf::RenderTarget& target);
    void render();
};

#endif //SFML_TEST_MAINWINDOW_H
