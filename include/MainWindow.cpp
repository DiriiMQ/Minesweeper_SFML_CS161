//
// Created by dirii on 09/12/2022.
//

#include "MainWindow.h"

Window::Window() {
    this->initVar();
    this->initNewWindow();
    this->initTextures();
    this->initSprites();
    this->initTexts();
}

Window::~Window() {
    delete this->window;
}

const bool Window::running() const {
    return this->window->isOpen();
}

void Window::initVar() {
    this->window = nullptr;
    this->currentScreen = MENU;
    this->mouseHeld = false;
    this->isCustomPressed = false;
    this->currentInputType = INPUT_WIDTH;
    this->ranking = Ranking();
    this->sideCell = 32;
    this->currentLevel = -1;
}

void Window::initNewWindow() {
    this->videoMode.width = 1760; // 55
    this->videoMode.height = 992; // 31 - 2 = 29
    this->window = new sf::RenderWindow(
            this->videoMode,
            "Minesweeper",
            sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Window::initTextures() {
    this->textureContinue.first.loadFromFile("../static/button/button_continue.png");
    this->textureContinue.first.setSmooth(true);
    this->textureContinue.second.loadFromFile("../static/button/button_continue_clickable.png");
    this->textureContinue.second.setSmooth(true);

    this->textureNewGame.first.loadFromFile("../static/button/button_new-game.png");
    this->textureNewGame.first.setSmooth(true);
    this->textureNewGame.second.loadFromFile("../static/button/button_new-game_clickable.png");
    this->textureNewGame.second.setSmooth(true);

    this->textureScoreBoard.first.loadFromFile("../static/button/button_scoreboard.png");
    this->textureScoreBoard.first.setSmooth(true);
    this->textureScoreBoard.second.loadFromFile("../static/button/button_scoreboard_clickable.png");
    this->textureScoreBoard.second.setSmooth(true);

    this->textureEasy.first.loadFromFile("../static/button/button_easy.png");
    this->textureEasy.first.setSmooth(true);
    this->textureEasy.second.loadFromFile("../static/button/button_easy_clicked.png");
    this->textureEasy.second.setSmooth(true);

    this->textureMedium.first.loadFromFile("../static/button/button_medium.png");
    this->textureMedium.first.setSmooth(true);
    this->textureMedium.second.loadFromFile("../static/button/button_medium_clicked.png");
    this->textureMedium.second.setSmooth(true);

    this->textureHard.first.loadFromFile("../static/button/button_hard.png");
    this->textureHard.first.setSmooth(true);
    this->textureHard.second.loadFromFile("../static/button/button_hard_clicked.png");
    this->textureHard.second.setSmooth(true);

    this->textureCustom.first.loadFromFile("../static/button/button_custom.png");
    this->textureCustom.first.setSmooth(true);
    this->textureCustom.second.loadFromFile("../static/button/button_custom_clicked.png");
    this->textureCustom.second.setSmooth(true);

    this->texturePlay.first.loadFromFile("../static/button/button_play.png");
    this->texturePlay.first.setSmooth(true);
    this->texturePlay.second.loadFromFile("../static/button/button_play_clickable.png");
    this->texturePlay.second.setSmooth(true);

    this->textureBack.first.loadFromFile("../static/button/button_back.png");
    this->textureBack.first.setSmooth(true);
    this->textureBack.second.loadFromFile("../static/button/button_back_clickable.png");
    this->textureBack.second.setSmooth(true);

    this->textureTextbox.loadFromFile("../static/stuff/textbox.png");
    this->textureTextbox.setSmooth(true);
    this->textureTextbox.setRepeated(true);

    this->textureGameObjects.loadFromFile("../static/stuff/gameObjects.jpg");
    this->textureGameObjects.setSmooth(true);
    this->textureGameObjects.setRepeated(true);

    this->textureFlower.loadFromFile("../static/stuff/flower.png");
    this->textureFlower.setSmooth(true);
    this->textureFlower.setRepeated(true);

    this->textureScoreboardFrame.loadFromFile("../static/stuff/frameScoreboard.png");
    this->textureScoreboardFrame.setSmooth(true);

    std::cout << "Loaded textures!\n";
}

void Window::initSprites() {
    this->buttonContinue = sf::Sprite(this->textureContinue.first);
    this->buttonNewGame = sf::Sprite(this->textureNewGame.first);
    this->buttonScoreBoard = sf::Sprite(this->textureScoreBoard.first);

    this->buttonEasy = sf::Sprite(this->textureEasy.first);
    this->buttonMedium = sf::Sprite(this->textureMedium.first);
    this->buttonHard = sf::Sprite(this->textureHard.first);
    this->buttonCustom = sf::Sprite(this->textureCustom.first);
    this->buttonPlay = sf::Sprite(this->texturePlay.first);

    this->buttonBack = sf::Sprite(this->textureBack.first);

    this->textboxWidth = sf::Sprite(this->textureTextbox);
    this->textboxHeight = sf::Sprite(this->textureTextbox);
    this->textboxMines = sf::Sprite(this->textureTextbox);

    this->flowerIcon = sf::Sprite(this->textureFlower);

    this->scoreboardFrame = sf::Sprite(this->textureScoreboardFrame);

    std::cout << "Loaded sprites!\n";
}

void Window::initTexts() {
    this->inputString = "";
    this->font.loadFromFile("../static/font/OpenSans.ttf");

    this->textWidth = sf::Text("Width", this->font, 26);
    this->textHeight = sf::Text("Height", this->font, 26);
    this->textMines = sf::Text("Mines", this->font, 26);
    this->textInputWidth = sf::Text("", this->font, 30);
    this->textInputHeight = sf::Text("", this->font, 30);
    this->textInputMines = sf::Text("", this->font, 30);

    this->textWidth.setFillColor(sf::Color(96, 96, 96));
    this->textHeight.setFillColor(sf::Color(96, 96, 96));
    this->textMines.setFillColor(sf::Color(96, 96, 96));

    this->textInputWidth.setFillColor(sf::Color(64, 64, 64));
    this->textInputHeight.setFillColor(sf::Color(64, 64, 64));
    this->textInputMines.setFillColor(sf::Color(64, 64, 64));

    this->gameTimerText = sf::Text("00:00", this->font, 40);
    this->gameRemainingMinesText = sf::Text("-1", this->font, 40);

    this->gameTimerText.setFillColor(sf::Color(96, 96, 96));
    this->gameRemainingMinesText.setFillColor(sf::Color(96, 96, 96));

    this->errorSizeText = sf::Text("", this->font, 26);
    this->errorSizeText.setFillColor(sf::Color::Red);

    this->textWin = sf::Text("WIN", this->font, 40);
    this->textWin.setFillColor(sf::Color::Green);

    this->textLose = sf::Text("LOSE", this->font, 40);
    this->textLose.setFillColor(sf::Color::Red);
}

void Window::initTextScoreboard() {
    std::vector<std::pair<std::string, int>> tmpEasy = this->ranking.getList(EASY);
    std::vector<std::pair<std::string, int>> tmpMedium = this->ranking.getList(MEDIUM);
    std::vector<std::pair<std::string, int>> tmpHard = this->ranking.getList(HARD);

    this->textRecordEasy.clear();
    this->textRecordMedium.clear();
    this->textRecordHard.clear();

    for (auto i : tmpEasy) {
        this->textRecordEasy.push_back({
                                               sf::Text(i.first, this->font, 26),
                                               sf::Text(std::to_string(i.second), this->font, 26)
                                       });
        this->textRecordEasy.back().first.setFillColor(sf::Color(96, 96, 96));
        this->textRecordEasy.back().second.setFillColor(sf::Color(96, 96, 96));
    }

    for (auto i : tmpMedium) {
        this->textRecordMedium.push_back({
                                                 sf::Text(i.first, this->font, 26),
                                                 sf::Text(std::to_string(i.second), this->font, 26)
                                         });
        this->textRecordMedium.back().first.setFillColor(sf::Color(96, 96, 96));
        this->textRecordMedium.back().second.setFillColor(sf::Color(96, 96, 96));
    }

    for (auto i : tmpHard) {
        this->textRecordHard.push_back({
                                               sf::Text(i.first, this->font, 26),
                                               sf::Text(std::to_string(i.second), this->font, 26)
                                       });
        this->textRecordHard.back().first.setFillColor(sf::Color(96, 96, 96));
        this->textRecordHard.back().second.setFillColor(sf::Color(96, 96, 96));
    }
}

void Window::moveOnAButton(sf::Sprite& button, std::pair<sf::Texture, sf::Texture>& texture) {
    if (this->isMovingOnButton(button)) {
//        std::cout << "Moving on the new game button\n";
        button.setTexture(texture.second);
    } else {
        button.setTexture(texture.first);
    }
}

bool Window::isMovingOnButton(sf::Sprite &button) {
//    std::cout << this->mousePosView.x << ' ' << this->mousePosView.y << '\n';
    return button.getGlobalBounds().contains(this->mousePosView);
}

void Window::updateMousePosition() {
    this->mousePos = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePos);
}

void Window::resetCursor() {
    this->textInputWidth.setString(this->removeLastCursor(this->textInputWidth.getString()));
    this->textInputHeight.setString(this->removeLastCursor(this->textInputHeight.getString()));
    this->textInputMines.setString(this->removeLastCursor(this->textInputMines.getString()));
}

std::string Window::removeLastCursor(std::string n) {
    if (n.size() && n.back() == '|')
        n.pop_back();
    return n;
}

std::string Window::secondsToString(sf::Time t) {
    int seconds = t.asSeconds();
    std::stringstream  ss;
    ss << std::setw(2) << std::setfill('0') << (seconds / 60) << ':' << std::setw(2) << (seconds % 60) << "\n";
    return ss.str();
}

void Window::pollEvent() {
    // event polling
    while (this->window->pollEvent(this->event)) {
        switch(this->event.type){
            case sf::Event::Closed:
                this->quitGame();
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Q){
                    std::cout << "You have pressed Q!\n";
                }
                if (this->event.key.code == sf::Keyboard::W){
                    std::cout << "You have pressed W!\n";
                }
                break;
        }
        switch (this->currentScreen) {
            case MENU:
                this->pollEventMenu();
                break;
            case GAME:
                this->pollEventGame();
                break;
            case SCORE_BOARD:
                this->pollEventScoreBoard();
                break;
            case CHOOSE_LEVEL:
                this->pollEventChooseLevel();
        }
    }
}

void Window::update() {
    this->pollEvent();

    this->updateMousePosition();

//    std::cout << "Current screen is " << this->currentScreen << '\n';

    switch (this->currentScreen) {
        case MENU:
            this->updateMenu();
            break;
        case GAME:
            this->updateGame();
            break;
        case SCORE_BOARD:
            this->updateScoreBoard();
            break;
        case CHOOSE_LEVEL:
            this->updateChooseLevel();
            break;
    }

//    std::cout << "Your mouse is at "
//            << this->mousePos.x << ' '
//            << this->mousePos.y << '\n';
}

void Window::render() {
    /*
     * clear old frames
     * create objects
     * display it
     * */

    this->window->clear(sf::Color::White);

    // drawing game here
//    this->renderEnemies();
    switch (this->currentScreen) {
        case MENU:
            this->renderMenu(*this->window);
            break;
        case GAME:
            this->renderGame(*this->window);
            break;
        case SCORE_BOARD:
            this->renderScoreBoard(*this->window);
            break;
        case CHOOSE_LEVEL:
            this->renderChooseLevel(*this->window);
            break;
    }

    this->window->display();
}

void Window::printBoard() {
    std::vector<std::vector<int>> board = this->ms->get_board(),
                                    state = this->ms->get_state();

    std::cout << "The current board\n";
    for (auto i : board){
        for (auto j : i)
                std::cout << j << ' ';
        std::cout << '\n';
    }

    std::cout << "The current state\n";
    for (auto i : state){
        for (auto j : i)
            std::cout << j << ' ';
        std::cout << '\n';
    }
}
