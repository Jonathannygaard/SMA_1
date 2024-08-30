#include "Shader.h"
#include "ShaderFileLoader.h"

unsigned int Shader::Program;

void Shader::CreateProgram()
{
    ShaderSource Source;
    Source.VertexShader = ShaderLoader::LoadShaderFromFile("Triangle.vs");
    Source.FragmentShader = ShaderLoader::LoadShaderFromFile("Triangle.fs");
    Program = glCreateProgram();
    const char* VertexSource = Source.VertexShader.c_str();
    const char* FragmentSource = Source.FragmentShader.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    int success;
    glShaderSource(vs, 1, &VertexSource, nullptr);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    char infoLog[512];
    if (!success)
    {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "VertexShader failed to compile\n" << infoLog << std::endl;
    }
    glShaderSource(fs, 1, &FragmentSource, nullptr);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cout << "FragmentShader failed to compile\n" << infoLog << std::endl;
    }
    glAttachShader(Program, vs);
    glAttachShader(Program, fs);
    glLinkProgram(Program);
    glDeleteShader(vs);
    glDeleteShader(fs);
}
