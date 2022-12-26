//
// Created by dirii on 20/12/2022.
//

#include "Ranking.h"

std::string RankingLevel::getCurrentTime() {
    time_t t = std::time(nullptr);
    struct tm *timeInfo = std::localtime(&t);
    char buffer[80];
    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeInfo);
    return std::string(buffer);
}

int RankingLevel::saveRecord(int duration) {
    std::string currentTime = getCurrentTime();
    int pos = 0;
    for (; pos < this->listTime.size(); ++pos) {
        if (this->listTime[pos].second > duration)
            break;
    }
    this->listTime.insert(this->listTime.begin() + pos, std::make_pair(currentTime, duration));

    this->saveRankToFile();
    return pos;
}

std::vector<std::pair<std::string, int>> RankingLevel::getListTime() {
    return this->listTime;
}

int RankingLevel::loadRankFromFile(std::string fileName) {
    std::ifstream cin_file(fileName);

    if (!cin_file.good())
        return _FILE_NOT_FOUND;

    this->listTime.clear();
    this->file = fileName;

    std::string date1, date2;
    int duration;
    while(cin_file >> date1 >> date2 >> duration){
        this->listTime.push_back(std::make_pair(date1 + ' ' + date2, duration));
    }

    cin_file.close();
    return _OK;
}

void RankingLevel::saveRankToFile() {
    std::ofstream cout_file(this->file);
    for (std::pair<std::string, int> i : this->listTime)
        cout_file << i.first << ' ' << i.second << '\n';
    cout_file.close();

    std::cout << "Saved rank into file!\n";
}

RankingLevel::RankingLevel(std::string fileName) {
    this->file = fileName;
    this->loadRankFromFile(fileName);
}

RankingLevel::~RankingLevel() {
    this->saveRankToFile();
}

RankingLevel::RankingLevel() {
    this->file = "../static/rank/test.dat";
    this->loadRankFromFile("../static/rank/test.dat");
}

void RankingLevel::reset() {
    listTime.clear();
}

void RankingLevel::printTime() {
    std::cout << "Ranking nao do\n";
    for (auto i : this->listTime)
        std::cout << i.first << ' ' << i.second << '\n';
    std::cout << "*****\n";
}

Ranking::Ranking() {
    this->init();
}

std::vector<std::pair<std::string, int>> Ranking::getList(int _level) {
    if (_level >= EASY && _level <= HARD)
        return this->level[_level].getListTime();
    return std::vector<std::pair<std::string, int>>();
}

int Ranking::saveRecord(int _level, int duration) {
    /**
     * Return the position of new record in this `_level`*/

    if (_level >= EASY && _level <= HARD)
        return this->level[_level].saveRecord(duration);

    return -1;
}

void Ranking::saveFile() {
    for (int i = EASY; i <= HARD; ++i)
        this->level[i].saveRankToFile();
}

Ranking::~Ranking() {
    this->saveFile();
}

void Ranking::resetLevel(int _level) {
    this->level[_level].reset();
}

void Ranking::init() {
    this->level[EASY] = RankingLevel(EASY_FILE);
    this->level[MEDIUM] = RankingLevel(MEDIUM_FILE);
    this->level[HARD] = RankingLevel(HARD_FILE);
}

void Ranking::reInit() {
    this->init();
}
