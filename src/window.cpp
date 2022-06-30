#include <window.hpp>
#include <utility.hpp>
#include <GLFW/glfw3.h>

//auto window = std::make_unique<Window>("hakugame");

Window window {"haku"};

Window::Window(const std::string_view title, const uint16_t w, const uint16_t h) {
    if (!glfwInit()) {
        terminate("ERROR: glfwInit() in file ", __FILE__);
    }
    width = w;
    height = h;

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
    width = w;
    height = h;
}

void Window::setPos(int x, int y) {
    glfwSetWindowPos(window, x, y);
}

void Window::onResize(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h); // Update opengl width height
}

GLFWwindow* Window::getGlfwWindowPtr() const {
    return window;
}

void Window::toggleFullScreen() {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    glfwSetWindowMonitor(window, monitor, 0, 0, width, height, GLFW_DONT_CARE);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
