#include "game.h"


Game::Game(GLuint width, GLuint height, GLboolean fullscreen)
{
	// Settings of console window
	SetWindowPos(GetConsoleWindow(), HWND_TOP, 0, 85, 500, 500, 0);
	SetConsoleTitle("The Legend of Zelda: Ocarina of Time Console");

	// Initializing GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return;
	}

	// Settings
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating game window
	if (fullscreen)	this->window = glfwCreateWindow(width, height, "The Legend of Zelda: Ocarina of Time", glfwGetPrimaryMonitor(), nullptr);
	else			this->window = glfwCreateWindow(width, height, "The Legend of Zelda: Ocarina of Time", nullptr, nullptr);

	if (this->window == nullptr)
	{
		std::cout << "Failed to open GLFW window!" << std::endl;
		glfwTerminate();
		return;
	}

	// Setting window as current GLFW context
	glfwMakeContextCurrent(this->window);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW!" << std::endl;
		glfwTerminate();
		return;
	}

	// Window icon
	GLFWimage icon[1];
	icon[0].pixels = SOIL_load_image("resources/common/triforce.png", &icon->width, &icon->height, 0, SOIL_LOAD_RGBA);
	glfwSetWindowIcon(this->window, 1, icon);

	// Window position
	glfwSetWindowPos(this->window, 500, 117);

	// Input mode
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

	// Cursor mode
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Game::~Game()
{
	glfwWindowShouldClose(this->window);
	glfwTerminate();
}



GLvoid Game::mainLoop()
{
	Scene scene;
	// GENERAL SETTINGS
	glClearColor(1.0f, 0.75f, 0.0f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// Cull faces with normals away from camera
	glEnable(GL_CULL_FACE);
	

	// MAIN LOOP
	GLdouble fps_limit_timer;
	GLdouble timer = glfwGetTime();
	GLuint fps = 0;
	do
	{
		if (glfwGetTime() - timer > 1) {
			std::cout << "FPS: " << fps << std::endl;
			fps = 0;
			timer = glfwGetTime();
			
		}
		else {
			fps++;
		}
		fps_limit_timer = glfwGetTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.computeInputs(this->window);
		scene.draw();

		glfwSwapBuffers(this->window);
		glfwPollEvents();

		// FPS LIMITER
		Sleep(1000 / 120 - (glfwGetTime() - fps_limit_timer));

	} while (glfwGetKey(this->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			 glfwWindowShouldClose(this->window) == 0);
}