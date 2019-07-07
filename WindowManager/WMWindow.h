#pragma once
#include <memory>
#include <functional>
#include <vector>
#include <string>

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
	std::string _title;
	ImGuiCond _cond;
	ImGuiWindowFlags _flags;
	bool _visibility;
	bool _pinned;
	std::vector<funcPtr> _drawables;

public:

	WMwindow(int width, int height, std::string title, ImGuiCond cond, bool visibility, bool pinned, ImGuiWindowFlags flags);
	~WMwindow();

	std::string getTitle();

	void addDrawables(func f);
	void removeDrawable(int i);

	void draw();

	void show();
	void hide();

	bool getPinned();
	void pin();
	void unpin();

	void toggleVisibility();

	void addFlags(ImGuiWindowFlags flags);
	void removeFlags(ImGuiWindowFlags flags);

};

WMwindow::WMwindow(int width, int height, std::string title, ImGuiCond cond, bool visibility, bool pinned, ImGuiWindowFlags flags)
	:
	_width(width),
	_height(height),
	_title(title),
	_cond(cond),
	_visibility(visibility),
	_pinned(pinned),
	_flags(flags)
{
	_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar;
}

WMwindow::~WMwindow()
{

}

std::string WMwindow::getTitle()
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
		ImGui::Begin(_title.c_str(), &_visibility, _flags);
		ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::MenuItem("Pin", NULL, true, !_pinned))
			{
				pin();
			}
			ImGui::EndMenuBar();
		}
		if (!_drawables.empty())
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
void WMwindow::toggleVisibility()
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
	_flags &= ~ImGuiWindowFlags_NoBringToFrontOnFocus;
}
void WMwindow::unpin()
{
	_pinned = false;
	_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void WMwindow::addFlags(ImGuiWindowFlags flags)
{
	_flags |= flags;
}
void WMwindow::removeFlags(ImGuiWindowFlags flags)
{
	_flags &= ~flags;
}