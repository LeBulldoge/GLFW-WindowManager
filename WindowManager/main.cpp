#include "WindowManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

const int WIDTH = 400;
const int HEIGHT = 400;
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

void createText()
{
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate,
		ImGui::GetIO().Framerate);
}
void createStuff()
{
	ImGui::BeginChildFrame(1, ImVec2(100, 100));
	ImGui::BeginChild(1, ImVec2(100, 100), false);
		ImGui::Text("Stuff");
		ImGui::Button("Yeet", ImVec2(50, 50));
	ImGui::EndChild();
	ImGui::EndChildFrame();
}

int main()
{
	initGLFW();
	initGLEW();
	WindowManager wm(5);
	wm.addWindow(100, 100, "0", ImGuiCond_FirstUseEver, true);
	wm.addWindow(100, 100, "1", ImGuiCond_FirstUseEver, true);
	wm.addWindow(100, 100, "2", ImGuiCond_FirstUseEver, true);
	wm.addWindow(100, 100, "3", ImGuiCond_FirstUseEver, true);
	wm.addWindow(100, 100, "4", ImGuiCond_FirstUseEver, true);

	wm[0]->addDrawables(&createText);
	wm[1]->addDrawables(&createStuff);

	wm[2]->hide();

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init("#version 130");

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