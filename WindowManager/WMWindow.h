#pragma once
#include <memory>
#include <functional>
#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class WMwindow;
using windowPtr = std::shared_ptr<WMwindow>;

class WMwindow
{
private:

	using func = std::function<void()>;
	using funcPtr = std::shared_ptr<func>;

	int _width;
	int _height;
	const char* _title;
	ImGuiCond _cond;
	ImGuiWindowFlags _flags;
	bool _visibility;
	bool _pinned;
	std::vector<funcPtr> _drawables;

public:

	WMwindow(int width, int height, const char* title, ImGuiCond cond, bool visibility, ImGuiWindowFlags flags);
	~WMwindow();
	const char* getTitle();
	void addDrawables(func f);
	void removeDrawable(int i);
	void draw();
	void show();
	void hide();
	bool getPinned();
	void pin();
	void unpin();
	void swapVisibility();
	void changeFlags(ImGuiWindowFlags flags);
	
};

WMwindow::WMwindow(int width, int height, const char* title, ImGuiCond cond, bool visibility, ImGuiWindowFlags flags)
	: 
	_width(width), 
	_height(height), 
	_title(title), 
	_cond(cond), 
	_visibility(visibility), 
	_flags(flags)
{
	_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	_pinned = false;
}

WMwindow::~WMwindow()
{
	
}

const char* WMwindow::getTitle()
{
	return _title;
}

void WMwindow::addDrawables(func f)
{
	_drawables.emplace_back(std::make_shared<func>(f));
}

void WMwindow::removeDrawable(int i)
{
	_drawables.erase(_drawables.begin() + i);
}

void WMwindow::draw()
{
	if (_visibility)
	{
		ImGui::SetNextWindowSize(ImVec2(_width, _height), _cond);
		ImGui::Begin(_title, &_visibility, _flags);
		ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::MenuItem("Pin", NULL, false, !_pinned))
			{
				pin();
			}
			ImGui::EndMenuBar();
		}
		if (_drawables.size())
		{
			for (funcPtr ptr : _drawables)
				std::invoke(*ptr);
		}
		ImGui::End();
		if (_pinned)
		{
			ImGui::SetWindowFocus();
		}
	}
	
}

void WMwindow::show()
{
	_visibility = true;
}
void WMwindow::hide()
{
	_visibility = false;
}
void WMwindow::swapVisibility()
{
	_visibility = !_visibility;
}

bool WMwindow::getPinned()
{
	return _pinned;
}
void WMwindow::pin()
{
	_pinned = true;
	_flags ^= ImGuiWindowFlags_NoBringToFrontOnFocus;
}
void WMwindow::unpin()
{
	_pinned = false;
	_flags ^= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void WMwindow::changeFlags(ImGuiWindowFlags flags)
{
	_flags = flags;
}