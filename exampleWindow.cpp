
#include "quarkWindow.h"
#include <chrono>

int main() {
    QuarkWindow *pWindow = 
        new QuarkWindow("Quark Window : Hello World!", 1200, 800);
    
    pWindow->texWidth = 2;
    pWindow->texHeight = 2;
    std::vector<float> tex = std::vector<float>(2 * 2 * 3);
    // Red
    tex[0]  = 1.0f;
    tex[1]  = 0.0f;
    tex[2]  = 0.0f;
    // Green
    tex[3]  = 0.0f;
    tex[4]  = 1.0f;
    tex[5]  = 0.0f;
    // Blue
    tex[6]  = 0.0f;
    tex[7]  = 0.0f;
    tex[8]  = 1.0f;
    // Yellow
    tex[9]  = 1.0f;
    tex[10] = 1.0f;
    tex[11] = 0.0f;

    pWindow->backBuffer = tex;
    pWindow->swapBuffers();
    
    std::thread renderThread(&QuarkWindow::run, pWindow);

    renderThread.join();

    delete pWindow;
    return 0;
}
