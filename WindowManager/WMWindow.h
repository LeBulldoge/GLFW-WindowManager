#pragma once
#include <memory>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class WMwindow;
using windowPtr = std::shared_ptr<WMwindow>;

class WMwindow
{
public:

	WMwindow(int width, int height, const char* title, int cond);
	~WMwindow();
	void addDrawables(void (*func)());
	void draw();

private:

	int _width;
	int _height;
	const char* _title;
	int _cond;

	void (*drawables)();
};

WMwindow::WMwindow(int width, int height, const char* title, int cond) : _width(width), _height(height), _title(title), _cond(cond)
{
	drawables = nullptr;
}

WMwindow::~WMwindow()
{

}

void WMwindow::addDrawables(void (*func)())
{
	drawables = func;
}

void WMwindow::draw()
{
	ImGui::SetNextWindowSize(ImVec2(_width, _height), _cond);
	ImGui::Begin(_title);
		ImGui::Text(_title);
		if (drawables)
		{
			drawables();
		}
	ImGui::End();
}