#ifndef SHADER_H
#define SHADER_H
#include "glad/glad.h" // include glad to get the required OpenGL headers
#include "GLFW/glfw3.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct ShaderSource
{
	std::string VertexShader;
	std::string FragmentShader;
};
namespace Shader
{
	extern unsigned int Program;
	
	// use/activate the shader
	void use();

	void CreateProgram();
	// utility uniform functions
	//void setBool(const std::string& name, bool value) const;
	//void setInt(const std::string& name, int value) const;
	//void setFloat(const std::string& name, float value) const;
};
#endif
