#include <Texture.h>
#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>
using namespace Resources;

void Texture::loadResource()
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(resourcePath.c_str(), &width, &height, &nrChannels, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}


void Texture::unloadResource()
{

}