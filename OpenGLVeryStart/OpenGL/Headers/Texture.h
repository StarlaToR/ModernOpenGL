#pragma once
#include <IResource.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Resources
{
	class Texture : public IResource
	{
	private:
		int width, height, nrChannels;
		
	public:
		GLuint texture;

		Texture(const std::string& filename)
		{
			setResourcePath(filename);
			loadResource();
		}

		void loadResource();
		void unloadResource();
	};
}