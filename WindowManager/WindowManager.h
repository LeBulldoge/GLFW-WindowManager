#pragma once
#include "WMwindow.h"
#include <vector>
#include <algorithm>
#include <optional>

class WindowManager
{
private:

	std::vector<windowPtr> _windows;
	windowPtr _pinnedPtr;

public:

	WindowManager();
	WindowManager(int size);
	~WindowManager();

	void addWindow(int width, int height, std::string title, ImGuiCond cond, bool visibility = true, bool pinned = false, ImGuiWindowFlags flags = 0);
	void destroyWindow(windowPtr ptr);
	void drawAll();
	void move(int a, int b);
	void resetPinnedStatus();
	std::optional<windowPtr> operator[](const unsigned int i);
	std::optional<windowPtr> operator[](std::string title);
	size_t size();
	bool empty();
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

void WindowManager::addWindow(int width, int height, std::string title, ImGuiCond cond, bool visibility, bool pinned, ImGuiWindowFlags flags)
{
	_windows.emplace_back(std::make_shared<WMwindow>(width, height, title, cond, visibility, pinned, flags));
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
		if (ptr->getPinned() && ptr != _pinnedPtr)
		{
			if (_pinnedPtr != nullptr) _pinnedPtr->unpin();
			_pinnedPtr = ptr;
			ImGui::SetWindowFocus(ptr->getTitle().c_str());
		}
	}
}

std::optional<windowPtr> WindowManager::operator[](const unsigned int i)
{
	if (_windows.size() > i)
	{
		return _windows[i];
	}
	return std::nullopt;
}
std::optional<windowPtr> WindowManager::operator[](std::string title)
{
	for (windowPtr ptr : _windows)
	{
		if (ptr->getTitle() == title) return ptr;
	}
	return std::nullopt;
}

size_t WindowManager::size()
{
	return _windows.size();
}
bool WindowManager::empty()
{
	return _windows.empty();
}