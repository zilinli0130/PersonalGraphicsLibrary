#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include "GL/glew.h"
#include< string>

using namespace std;
class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	bool LoadTexture(const string& file_name, bool min_maps = true);
	void BindTexture(GLuint text_unit = 0);

private:

	GLuint _texture;

};

#endif TEXTURE_2D_H

