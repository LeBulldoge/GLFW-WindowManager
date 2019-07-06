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

	void addWindow(int width, int height, const char* title, int cond, bool visibility);
	void destroyWindow(windowPtr ptr);
	void drawAll();
	windowPtr operator[](int i);
	

private:

	std::vector<windowPtr> _windows;

};

WindowManager::WindowManager()
{

}

WindowManager::WindowManager(int size)
{
	_windows.reserve(size);
}

WindowManager::~WindowManager()
{

}

void WindowManager::addWindow(int width, int height, const char* title, int cond, bool visibility)
{
	_windows.emplace_back(std::make_shared<WMwindow>(width, height, title, cond, visibility));
}

void WindowManager::destroyWindow(windowPtr ptr)
{
	ptr->~WMwindow();
	_windows.erase(std::remove(_windows.begin(), _windows.end(), ptr), _windows.end());
}

void WindowManager::drawAll()
{
	for (windowPtr ptr : _windows)
	{
		ptr->draw();
	}
}

windowPtr WindowManager::operator[](const int i)
{
	return _windows[i];
}