#include "GraphicLib/includes/shader_program.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram():
	_shader_program(0)
{
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_shader_program);
}

bool ShaderProgram::LoadShaders(const char* vertex_shader_name, const char* fragment_shader_name)
{

    std::string vertex_shader_string = FileToString(vertex_shader_name);
    std::string fragment_shader_string = FileToString(fragment_shader_name);
    const char* vertex_shader = vertex_shader_string.c_str();
    const char* fragment_shader = fragment_shader_string.c_str();
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vertex_shader, NULL);
    glShaderSource(fs, 1, &fragment_shader, NULL);

    glCompileShader(vs);
    CheckCompileError(VERTEX, vs);
    glCompileShader(fs);
    CheckCompileError(FRAGMENT, fs);
    
    _shader_program = glCreateProgram();
    if (_shader_program == 0)
    {
        std::cerr << "Unable to create shader program!" << std::endl;
        return false;
    }
    glAttachShader(_shader_program, vs);
    glAttachShader(_shader_program, fs);
    glLinkProgram(_shader_program);
    CheckCompileError(PROGRAM);
   
    glDeleteShader(vs);
    glDeleteShader(fs);

    _uniform_locations.clear();
	return true;
}

void ShaderProgram::Use()
{
	if (_shader_program > 0)
	{
		glUseProgram(_shader_program);
	}
}

void ShaderProgram::SetUniform(const char* name, const glm::vec2& v)
{
    GLint location = GetUniformLocation(name);
    glUniform2f(location, v.x, v.y);
}

void ShaderProgram::SetUniform(const char* name, const glm::vec3& v)
{
    GLint location = GetUniformLocation(name);
    glUniform3f(location, v.x, v.y, v.z);
}

void ShaderProgram::SetUniform(const char* name, const glm::vec4& v)
{
    GLint location = GetUniformLocation(name);
    glUniform4f(location, v.x, v.y, v.z, v.w);
}

void ShaderProgram::SetUniform(const char* name, const glm::mat4& m)
{
    GLint location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m));
}

string ShaderProgram::FileToString(const string& file_name)
{
	std::stringstream ss;
	std::ifstream file;

	try 
	{
		file.open(file_name, std::ios::in);
		if (!file.fail())
		{
			ss << file.rdbuf();
		}
		file.close();
	}
	catch (std::exception ex) 
	{
		std::cerr << "Failed to read shader file name!" << std::endl;
	}
    return ss.str();
}

void ShaderProgram::CheckCompileError(ShaderType type, GLuint name)
{
    int status = 0;
    switch (type)
    {
    case PROGRAM:
        glGetProgramiv(_shader_program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint length = 0;
            glGetProgramiv(_shader_program, GL_INFO_LOG_LENGTH, &length);
            string error_log(length, ' ');
            glGetProgramInfoLog(_shader_program, length, &length, &error_log[0]);
            std::cerr << "Failed to link shader program: " << error_log << std::endl;
        }
        break;
    case VERTEX:
    case FRAGMENT:
        glGetShaderiv(name, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLint length = 0;
            glGetShaderiv(name, GL_INFO_LOG_LENGTH, &length);
            string error_log(length, ' ');
            glGetShaderInfoLog(_shader_program, length, &length, &error_log[0]);
            std::cerr << "Failed to compile shader: " << error_log << std::endl;
        }
        break;
    default:
        break;
    }
}

GLint ShaderProgram::GetUniformLocation(const char* name)
{
    std::map<std::string, GLint>::iterator it = _uniform_locations.find(name);
    if (it == _uniform_locations.end())
    {
        _uniform_locations[name] = glGetUniformLocation(_shader_program, name);
    }
    return _uniform_locations[name];
}
