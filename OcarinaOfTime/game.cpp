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


	// GLFW Window Hints
	// Number of Samples for Anti-Aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);
	// Using OpenGL v3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// OpenGL Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Window not resizeable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	// Creating game window
	if (fullscreen)
	{
		// Creating fullscreen window
		this->window = glfwCreateWindow(width, height, "The Legend of Zelda: Ocarina of Time", glfwGetPrimaryMonitor(), nullptr);
	}
	else
	{
		// Creating non-fullscreen window
		this->window = glfwCreateWindow(width, height, "The Legend of Zelda: Ocarina of Time", nullptr, nullptr);
	}

	if (this->window == nullptr)
	{
		std::cout << "Failed to open GLFW window!" << std::endl;
		glfwTerminate();
		return;
	}


	// Setting window as current GLFW context
	glfwMakeContextCurrent(this->window);
	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW!" << std::endl;
		return;
	}


	// Window settings
	// Window icon
	// Array of icons: System chooses closest to match platform and system settings
	GLFWimage icon[1];
	icon[0].pixels = SOIL_load_image("resources/common/triforce.png", &icon[0].width, &icon[0].height, 0, SOIL_LOAD_RGBA);
	glfwSetWindowIcon(this->window, 1, icon);

	// Window position
	glfwSetWindowPos(this->window, 500, 117);

	// Keyboard input mode
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

	// Disable mouse cursor
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	this->mainLoop();
}
Game::~Game()
{
	// Close the Window
	if (this->window != nullptr)
	{
		glfwDestroyWindow(this->window);
	}

	// Terminate GLFW
	glfwTerminate();
}


GLvoid Game::mainLoop()
{
	Scene scene(this->window);
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