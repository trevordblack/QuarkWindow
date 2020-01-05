#include <assert.h>
#include "quarkWindow.h"

static void quarkWindowErrorCB(int error, const char* desc) {
    fprintf(stderr, "Error in glfw:\n  Error #: %i\n  Description: %s\n",
                     error, desc);
}

static void quarkWindowResizeCB(GLFWwindow *hWindow, int width, int height) {
    QuarkWindow* qw = 
        static_cast<QuarkWindow*>(glfwGetWindowUserPointer(hWindow));
    assert(qw);
    qw->resize(width, height);
}

QuarkWindow::QuarkWindow(const std::string &name, int width, int height) 
    : windowName(name), fbWidth(width), fbHeight(height) {
    resize(width, height);
}

QuarkWindow::~QuarkWindow() {
    glfwDestroyWindow(hWindow);
    glfwTerminate();
}

void QuarkWindow::draw() {
    if (fbTexture == 0)
        glGenTextures(1, &fbTexture);

    glBindTexture(GL_TEXTURE_2D, fbTexture);
    GLenum texFormat = GL_RGB;
    GLenum texelType = GL_FLOAT;
    glTexImage2D(GL_TEXTURE_2D, 0, texFormat, texWidth, texHeight, 0, GL_RGB,
                 texelType, frontBuffer.data());

    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, fbTexture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glDisable(GL_DEPTH_TEST);

    glViewport(0, 0, fbWidth, fbHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, (float) fbWidth, 0.0f, (float) fbHeight, -1.0f, 1.0f);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
 
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f, (float) fbHeight, 0.0f);
 
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f((float) fbWidth, (float) fbHeight, 0.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f((float) fbWidth, 0.0f, 0.0f);
    }
    glEnd();
}

void QuarkWindow::resize(int width, int height) {
    fbWidth = width;
    fbHeight = height;
}

void QuarkWindow::swapBuffers() {
    frontBuffer.swap(backBuffer);
}

void QuarkWindow::run() {
    glfwSetErrorCallback(quarkWindowErrorCB);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    hWindow = glfwCreateWindow(fbWidth, fbHeight, 
                               windowName.c_str(), NULL, NULL);
    if (!hWindow) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(hWindow, this);
    glfwMakeContextCurrent(hWindow);
    glfwSwapInterval( 1 );

    glfwSetFramebufferSizeCallback(hWindow, quarkWindowResizeCB);
    while (!glfwWindowShouldClose(hWindow)) {
        draw();
        glfwSwapBuffers(hWindow);
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/QW_REFRESH_RATE));
    }
}
