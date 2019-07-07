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

	void addWindow(int width, int height, const char* title, ImGuiCond cond, bool visibility = true, ImGuiWindowFlags flags = ImGuiWindowFlags_NoBringToFrontOnFocus);
	void destroyWindow(windowPtr ptr);
	void drawAll();
	void move(int a, int b);
	void resetPinnedStatus();
	windowPtr operator[](int i);
	

private:

	std::vector<windowPtr> _windows;
	windowPtr _pinned;
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

void WindowManager::addWindow(int width, int height, const char* title, ImGuiCond cond, bool visibility, ImGuiWindowFlags flags)
{
	_windows.emplace_back(std::make_shared<WMwindow>(width, height, title, cond, visibility, flags));
	if (_windows.size() == 1)
	{
		_windows[0]->pin();
		_pinned = _windows[0];
	}
}

void WindowManager::destroyWindow(windowPtr ptr)
{
	ptr->~WMwindow();
	_windows.erase(std::remove(_windows.begin(), _windows.end(), ptr), _windows.end());
}

void WindowManager::drawAll()
{
	resetPinnedStatus();
	for (windowPtr ptr : _windows)
	{
		ptr->draw();
	}
}

void WindowManager::move(const int a, const int b)
{
	std::swap(_windows[a], _windows[b]);
}

void WindowManager::resetPinnedStatus()
{
	for (windowPtr ptr : _windows)
	{
		if (ptr->getPinned() && ptr != _pinned)
		{
			_pinned->unpin();
			_pinned = ptr;
			ImGui::SetWindowFocus(ptr->getTitle());
		}
	}
}

windowPtr WindowManager::operator[](const int i)
{
	return _windows[i];
}