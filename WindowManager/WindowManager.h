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

	void addWindow(int width, int height, const char* title, int cond);
	void destroyWindow(windowPtr ptr);
	windowPtr operator[](int i);

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

void WindowManager::addWindow(int width, int height, const char* title, int cond)
{
	windows.emplace_back(std::make_shared<WMwindow>(width, height, title, cond));
	main = windows[0];
}

void WindowManager::destroyWindow(windowPtr ptr)
{
	ptr->~WMwindow();
	windows.erase(std::remove(windows.begin(), windows.end(), ptr), windows.end());
}

windowPtr WindowManager::operator[](int i)
{
	return windows[i];
}