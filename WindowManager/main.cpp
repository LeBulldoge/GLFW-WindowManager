#include "WindowManager.h"
#include <vector>
#include <string>

const int WIDTH = 400;
const int HEIGHT = 400;

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		int attrib = glfwGetWindowAttrib(window, GLFW_FLOATING);
		glfwSetWindowAttrib(window, GLFW_FLOATING, attrib ? 0 : 1);
	}
}

int main()
{
	initGLFW();
	initGLEW();
	WindowManager wm(5);

	wm.addWindow(0, WIDTH, HEIGHT, "0", NULL, NULL);

	for (int i = 1; i < 5; i++)
	{
		wm.addWindow(i, WIDTH, HEIGHT, std::to_string(i).c_str(), NULL, NULL);
	}
	wm.addKeyCallback(key_callback);

	while (!wm.shouldClose())
	{
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}