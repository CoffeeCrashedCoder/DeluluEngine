#include "Window.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

Window::Window( int width, int height, int max_width, int max_height, const std::string &title )
    :m_width(width), m_height(height), m_max_width(max_width), m_max_height(max_height)
{
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
    glfwWindowHint(GLFW_POSITION_X, (m_max_width/2)-(m_width/2));
    glfwWindowHint(GLFW_POSITION_Y, (m_max_height/2)-(m_height/2));

    m_handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if(!m_handle)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_handle);
    glfwSetFramebufferSizeCallback(m_handle, framebufferResizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");
}

Window::~Window()
{
    glfwDestroyWindow(m_handle);
    glfwTerminate();
}

bool Window::ShouldClose() const {return glfwWindowShouldClose(m_handle);}
void Window::PollEvents() const {glfwPollEvents();}
void Window::SwapBuffers() const {glfwSwapBuffers(m_handle);}
void Window::framebufferResizeCallback( GLFWwindow *window, int width, int height )
{glViewport(0,0,width,height);}
