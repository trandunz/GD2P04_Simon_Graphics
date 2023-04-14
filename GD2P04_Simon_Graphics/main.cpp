#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

GLFWwindow* RenderWindow{};

void InitGL();
void InitGLFW();

void Start();
void Update();
void Render();

int Cleanup();

int main()
{
	InitGLFW();
	InitGL();

	Start();
	Update();

	return Cleanup();
}

void InitGL()
{
	if (glewInit() != GLEW_OK)
		exit(0);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void InitGLFW()
{
	if (glfwInit() != GLFW_TRUE)
		exit(0);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	RenderWindow = glfwCreateWindow(800, 800, "", NULL, NULL);

	glfwMakeContextCurrent(RenderWindow);

	//glfwSetKeyCallback(RenderWindow, KeyCallback);
	//glfwSetCursorPosCallback(RenderWindow, CursorCallback);
	//glfwSetMouseButtonCallback(RenderWindow, CursorClickCallback);
}

void Start()
{
}

void Update()
{
	while (glfwWindowShouldClose(RenderWindow) == false)
	{
		glfwPollEvents();


		Render();
	}
}

void Render()
{
}

int Cleanup()
{

	return 0;
}