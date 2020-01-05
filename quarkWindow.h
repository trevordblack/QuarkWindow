#ifndef QUARK_WINDOW_H
#define QUARK_WINDOW_H

#include <vector>
#include <string>
#include <thread>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <GL/gl.h>

#ifndef QW_REFRESH_RATE
#define QW_REFRESH_RATE 60
#endif //!QW_REFRESH_RATE

class QuarkWindow {
public:
    QuarkWindow(const std::string &name, int width, int height);
    ~QuarkWindow();

    virtual void run();
    virtual void draw();
    virtual void resize(int width, int height);
    virtual void swapBuffers();

    GLFWwindow *hWindow { nullptr };
    std::string windowName;
    int fbWidth;
    int fbHeight;
    std::vector<float> frontBuffer;
    std::vector<float> backBuffer;
    int texWidth;
    int texHeight;
    GLuint fbTexture {0};
};

#endif //!QUARK_WINDOWS_H
