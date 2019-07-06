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
	int _cond;
	std::vector<funcPtr> drawables;

public:

	WMwindow(int width, int height, const char* title, int cond);
	~WMwindow();
	void addDrawables(func f);
	void draw();
};

WMwindow::WMwindow(int width, int height, const char* title, int cond) : _width(width), _height(height), _title(title), _cond(cond)
{
	
}

WMwindow::~WMwindow()
{
	
}

void WMwindow::addDrawables(func f)
{
	drawables.emplace_back(std::make_shared<func>(f));
}

void WMwindow::draw()
{
	ImGui::SetNextWindowSize(ImVec2(_width, _height), _cond);
	ImGui::Begin(_title);
		if (drawables.size())
		{
			for (funcPtr ptr : drawables)
				std::invoke(*ptr);
		}
	ImGui::End();
}