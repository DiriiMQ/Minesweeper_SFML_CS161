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
