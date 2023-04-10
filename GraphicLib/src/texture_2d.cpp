#include "GraphicLib/includes/texture_2d.h"
#include <iostream>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "GraphicLib/includes/stb_image.h"

Texture2D::Texture2D():
	_texture(0)
{
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_texture);
}

bool Texture2D::LoadTexture(const string& file_name, bool min_maps)
{
	int width, height, components;

	// Load image
	unsigned char* image_data = stbi_load(file_name.c_str(), &width, &height, 
										  &components, STBI_rgb_alpha);

	if (image_data == NULL)
	{	
		std::cerr << "Failed to load image: " << file_name << std::endl;
		return false;
	}

	// Invert image
	int width_in_bytes = width * 4;
	unsigned char* top = NULL;
	unsigned char* bottom = NULL;
	unsigned char temp = 0;
	for (int row = 0; row < height / 2; row++)
	{
		top = image_data + row * width_in_bytes;
		bottom = image_data + (height - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++)
		{
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// Set the texture wrapping/filtering options (on the currently bound texture object)
	// GL_CLAMP_TO_EDGE
	// GL_REPEAT
	// GL_MIRRORED_REPEAT
	// GL_CLAMP_TO_BORDER
	// GL_LINEAR
	// GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	if (min_maps)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(image_data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
	
}

void Texture2D::BindTexture(GLuint text_unit)
{
	assert(text_unit >= 0 && text_unit < 32);

	glActiveTexture(GL_TEXTURE0 + text_unit);
	glBindTexture(GL_TEXTURE_2D, _texture);
}
