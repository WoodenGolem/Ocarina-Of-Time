#include "resource_manager.h"



ResourceManager::ResourceManager(){
}
ResourceManager::~ResourceManager()
{
	for (int i = 0; i < this->meshes.size(); i++)
	{
		delete this->meshes[i];
	}

	for (int i = 0; i < this->textures.size(); i++)
	{
		delete this->textures[i];
	}
}

GLvoid ResourceManager::load()
{
	this->shader_programs.push_back(this->loadShader("resources/shader/vertex_shader.vert", 
													 "resources/shader/fragment_shader.frag"));

	this->meshes.push_back(new Mesh("resources/meshes/cube1x1.obj"));	  // 0
	this->meshes.push_back(new Mesh("resources/meshes/terrain.obj"));	  // 1
	this->meshes.push_back(new Mesh("resources/meshes/liteterrain.obj")); // 2
	this->meshes.push_back(new Mesh("resources/meshes/player.obj"));	  // 3
	this->meshes.push_back(new Mesh("resources/meshes/suzanne.obj"));	  // 4
	//this->meshes.push_back(new Mesh("resources/meshes/pyramid.obj"));	  // 
	this->meshes.push_back(new Mesh("resources/meshes/link.obj"));		  // 5
	//this->meshes.push_back(new Mesh("resources/meshes/sphere1x1.obj")); // 


	this->textures.push_back(new Texture({ this->loadTexture("resources/textures/link.bmp"),
							 GLuint(glGetUniformLocation(this->shader_programs[0], "TextureSampler")) }));
	this->textures.push_back(new Texture({ this->loadTexture("resources/textures/red.bmp"),
							 GLuint(glGetUniformLocation(this->shader_programs[0], "TextureSampler")) }));
	this->textures.push_back(new Texture({ this->loadTexture("resources/textures/green.bmp"),
							 GLuint(glGetUniformLocation(this->shader_programs[0], "TextureSampler")) }));
	this->textures.push_back(new Texture({ this->loadTexture("resources/textures/player.bmp"),
							 GLuint(glGetUniformLocation(this->shader_programs[0], "TextureSampler")) }));
}

GLuint ResourceManager::shader(GLuint id) {
	if (id >= this->shader_programs.size() || id < 0) {
		return 0;
	}
	else {
		return this->shader_programs[id];
	}
}
Texture* ResourceManager::texture(GLuint id)
{
	if (id >= this->textures.size() || id < 0) {
		return 0;
	}
	else {
		return this->textures[id];
	}
}
Mesh* ResourceManager::mesh(GLuint id)
{
	if (id >= this->meshes.size() || id < 0) {
		return 0;
	}
	else {
		return this->meshes[id];
	}
}

GLuint ResourceManager::loadShader(std::string vertex_file_path, std::string fragment_file_path)
{
	using namespace std;

	// Create the shaders
	GLuint vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string vertex_shader_code;
	ifstream vertex_shader_stream(vertex_file_path, ios::in);
	if (vertex_shader_stream.is_open())
	{
		stringstream sstr;
		sstr << vertex_shader_stream.rdbuf();
		vertex_shader_code = sstr.str();
		vertex_shader_stream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory?\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	string fragment_shader_code;
	ifstream fragment_shader_stream(fragment_file_path, ios::in);
	if (fragment_shader_stream.is_open())
	{
		stringstream sstr;
		sstr << fragment_shader_stream.rdbuf();
		fragment_shader_code = sstr.str();
		fragment_shader_stream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory?\n", vertex_file_path);
		getchar();
		return 0;
	}


	// Shader Compilation
	GLint result = GL_FALSE;
	int info_log_length;

	// Compile Vertex Shader
	printf("Compiling shader: %s\n", vertex_file_path.c_str());
	char const* vertex_source_pointer = vertex_shader_code.c_str();
	glShaderSource(vertex_shader_ID, 1, &vertex_source_pointer, NULL);
	glCompileShader(vertex_shader_ID);

	// Check Vertex Shader
	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertex_shader_ID, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		std::vector<char> vertex_shader_error_message(info_log_length + 1);
		glGetShaderInfoLog(vertex_shader_ID, info_log_length, NULL, &vertex_shader_error_message[0]);
		printf("%s\n", &vertex_shader_error_message[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader: %s\n", fragment_file_path.c_str());
	char const* fragment_source_pointer = fragment_shader_code.c_str();
	glShaderSource(fragment_shader_ID, 1, &fragment_source_pointer, NULL);
	glCompileShader(fragment_shader_ID);

	// Check Fragment Shader
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_shader_ID, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		std::vector<char> fragment_shader_error_message(info_log_length + 1);
		glGetShaderInfoLog(fragment_shader_ID, info_log_length, NULL, &fragment_shader_error_message[0]);
		printf("%s\n", &fragment_shader_error_message[0]);
	}


	// Link the program
	printf("Linking program...\n");
	GLuint program_ID = glCreateProgram();
	glAttachShader(program_ID, vertex_shader_ID);
	glAttachShader(program_ID, fragment_shader_ID);
	glLinkProgram(program_ID);

	// Check the program
	glGetProgramiv(program_ID, GL_LINK_STATUS, &result);
	glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
		std::vector<char> program_error_message(info_log_length + 1);
		glGetProgramInfoLog(program_ID, info_log_length, NULL, &program_error_message[0]);
		printf("%s\n", &program_error_message[0]);
	}


	glDetachShader(program_ID, vertex_shader_ID);
	glDetachShader(program_ID, fragment_shader_ID);

	glDeleteShader(vertex_shader_ID);
	glDeleteShader(fragment_shader_ID);

	return program_ID;
}
GLuint ResourceManager::loadTexture(std::string imagepath)
{
	std::cout << "Loading Texture..." << std::endl;

	GLint width;
	GLint height;
	unsigned char* data = SOIL_load_image(imagepath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	GLuint texture_ID;
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);


	// Standard Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/*
	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);
	*/

	return texture_ID;
}