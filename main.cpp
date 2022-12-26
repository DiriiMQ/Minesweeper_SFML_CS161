#include "MainWindow.h"

int main()
{
    // init window
    Window window;

    // game loop
    while (window.running()) {
        // update
        window.update();

        //render
        window.render();
    }
    return 0;
}

// for testing ranking library
//#include "Ranking.h"
//#include <iostream>
//
//int main(){
//    Ranking ranking;
//    std::vector<std::pair<std::string, int>> rankEasy = ranking.getList(HARD);
//    for (auto i : rankEasy) {
//        std::cout << i.first << " | " << i.second << '\n';
//    }
//}