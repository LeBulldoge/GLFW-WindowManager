#pragma once
#include "WMWindow.h"
#include <vector>
#include <algorithm>

class WindowManager
{
public:

	WindowManager();
	WindowManager(int size);
	~WindowManager();

	windowPtr addWindow(int o, int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	void destroyWindow(windowPtr ptr);
	bool shouldClose();
	void addKeyCallback(void* func);

private:

	std::vector<windowPtr> windows;
	windowPtr main;
};

WindowManager::WindowManager()
{
}

WindowManager::WindowManager(int size)
{
	windows.reserve(size);
}

WindowManager::~WindowManager()
{
}

windowPtr WindowManager::addWindow(int o, int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	windows.emplace_back(std::make_shared<WMwindow>(o, width, height, title, monitor, share));
	main = windows[0];
	return windows[o];
}

void WindowManager::destroyWindow(windowPtr ptr)
{
	ptr->~WMwindow();
	windows.erase(std::remove(windows.begin(), windows.end(), ptr), windows.end());
}

bool WindowManager::shouldClose()
{
	if (!windows.size()) return true;
	for (windowPtr p : windows)
	{
		if (glfwWindowShouldClose(p->getWindow()))
		{
			if (p == main) return true;
			destroyWindow(p);
		}
	}
	return false;
}

void WindowManager::addKeyCallback(void* func)
{
	for (windowPtr p : windows)
	{
		p->addKeyCallback(func);
	}
}