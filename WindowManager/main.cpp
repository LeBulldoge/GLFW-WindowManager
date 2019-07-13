#include "WindowManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

const int WIDTH = 1280;
const int HEIGHT = 720;
static GLFWwindow* window;

int initGLFW()
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "ImGui window manager", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	return 0;
}

int initGLEW()
{
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	return 0;
}

void createText(std::string a)
{
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate,
		ImGui::GetIO().Framerate);
	ImGui::Text(a.c_str());
}
void createStuff()
{
	ImGui::BeginChildFrame(1, ImVec2(100, 100));
	ImGui::BeginChild(1, ImVec2(100, 100), false);
	ImGui::Text("Stuff");
	ImGui::Button("Button", ImVec2(50, 50));
	ImGui::EndChild();
	ImGui::EndChildFrame();
}

int main()
{
	initGLFW();
	initGLEW();

	WindowManager wm(5);
	wm.addWindow(200, 200, "0", ImGuiCond_FirstUseEver);
	wm.addWindow(200, 200, "1", ImGuiCond_FirstUseEver);
	wm.addWindow(200, 200, "2", ImGuiCond_FirstUseEver);
	wm.addWindow(200, 200, "3", ImGuiCond_FirstUseEver);
	wm.addWindow(200, 200, "4", ImGuiCond_FirstUseEver);

	std::string test = "This is a demo.";

	if (wm["3"].has_value()) wm["3"].value()->addDrawables([&test]()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / ImGui::GetIO().Framerate,
			ImGui::GetIO().Framerate);
		ImGui::Text(test.c_str());
	});
	if (wm[4].has_value()) wm[4].value()->addDrawables([]()
	{
		ImGui::BeginChildFrame(1, ImVec2(100, 100));
		ImGui::BeginChild(1, ImVec2(100, 100), false);
		ImGui::Text("Stuff");
		ImGui::Button("Button", ImVec2(50, 50));
		ImGui::EndChild();
		ImGui::EndChildFrame();
	});

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init("#version 330");

	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		wm.drawAll();

		ImGui::Render();
		ImGui::EndFrame();

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}