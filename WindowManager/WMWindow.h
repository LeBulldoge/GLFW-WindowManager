#pragma once
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WMwindow;
using windowPtr = std::shared_ptr<WMwindow>;

class WMwindow
{
public:

	WMwindow(int o, int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	~WMwindow();
	GLFWwindow* getWindow();
	void addKeyCallback(void* func);

private:

	int order;
	GLFWwindow* glWindow;
};

WMwindow::WMwindow(int o, int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) : order(o)
{
	glWindow = glfwCreateWindow(width, height, title, monitor, share);
	if (!glWindow)
	{
		glfwTerminate();
	}
}

WMwindow::~WMwindow()
{
	glfwDestroyWindow(glWindow);
	glWindow = nullptr;
}

GLFWwindow* WMwindow::getWindow()
{
	return glWindow;
}

void WMwindow::addKeyCallback(void* func)
{
	glfwSetKeyCallback(glWindow, (GLFWkeyfun)func);
}