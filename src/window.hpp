#pragma once 
#include <string_view>
#include <stdint.h>
#include <memory>

class GLFWwindow;

class Window {
    GLFWwindow* window;
    bool fullScreen;
    
public:
    int width;
    int height;
    Window(const std::string_view title="None", const uint16_t width=640, const uint16_t height=480);
    void setSize(int w, int h);
    void setPos(int w, int h);
    void onResize(int w, int h);
    GLFWwindow* getGlfwWindowPtr() const;
    void toggleFullScreen();
    ~Window();
};

extern Window window;