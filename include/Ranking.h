//
// Created by dirii on 20/12/2022.
//

#ifndef MINESWEEPER_GUI_RANKING_H
#define MINESWEEPER_GUI_RANKING_H

#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>

#define EASY 0
#define MEDIUM 1
#define HARD 2

#define EASY_FILE "../static/rank/easy.dat"
#define MEDIUM_FILE "../static/rank/medium.dat"
#define HARD_FILE "../static/rank/hard.dat"

#define _OK 0
#define _FILE_NOT_FOUND -1

class RankingLevel{
private:
    std::string file;
    std::vector<std::pair<std::string, int>> listTime;
public:
    RankingLevel();
    RankingLevel(std::string fileName);
    ~RankingLevel();

    std::string getCurrentTime();
    int saveRecord(int duration);
    std::vector<std::pair<std::string, int>> getListTime();
    int loadRankFromFile(std::string fileName);
    void saveRankToFile();
    void reset();
    void printTime(); // for testing
};

class Ranking{
private:
    RankingLevel level[3];

    void init();
public:
    Ranking();
    ~Ranking();
    void reInit();
    std::vector<std::pair<std::string, int>> getList(int _level);
    int saveRecord(int _level, int duration);
    void saveFile();
    void resetLevel(int _level);
};

#endif //MINESWEEPER_GUI_RANKING_H
