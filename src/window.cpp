#include "window.hpp"
#include "utility.hpp"
#include <GLFW/glfw3.h>

//auto window = std::make_unique<Window>("hakugame");

Window::Window(const std::string_view title, const uint16_t width, const uint16_t height) {
    if (!glfwInit()) {
        terminate("ERROR: glfwInit() in file ", __FILE__);
    }

    window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        terminate("ERROR: creating window");
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);

    glfwSetWindowSizeCallback(window, [] (GLFWwindow* wnd, int w, int h) {
        static_cast<Window*>(glfwGetWindowUserPointer(wnd))->onResize(w, h);
    });
}

void Window::setSize(int w, int h) {
    glfwGetWindowSize(window, &w, &h);
    size = {w, h};
}

void Window::setPos(int x, int y) {
    glfwSetWindowPos(window, x, y);
}

void Window::onResize(int w, int h) {
    size = {w, h};
    glViewport(0, 0, w, h); // Update opengl width height
}

GLFWwindow* Window::getGlfwWindowPtr() const {
    return window;
}

Window::Size Window::getSize() const {
    return size;
}

void Window::toggleFullScreen() {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    glfwSetWindowMonitor(window, monitor, 0, 0, size.width, size.height, GLFW_DONT_CARE);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
