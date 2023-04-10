#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include <map>

using namespace std;
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	
	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	bool LoadShaders(const char* vertex_shader_name, const char* fragment_shader_name);
	void Use();
	void SetUniform(const char* name, const glm::vec2& v); 
	void SetUniform(const char* name, const glm::vec3& v);
	void SetUniform(const char* name, const glm::vec4& v);
	void SetUniform(const char* name, const glm::mat4& m);

private:
	string FileToString(const string& file_name);
	void CheckCompileError(ShaderType type, GLuint name = 0);
	GLint GetUniformLocation(const char* name);

private:
	GLuint _shader_program;
	std::map<std::string, GLint> _uniform_locations;

};

#endif 