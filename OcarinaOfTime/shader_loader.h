#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <fstream>
#include <sstream>
#include <vector>

#include "declarations.h"


GLuint loadShader(std::string vertex_file, std::string fragment_file);


#endif // !SHADER_H

