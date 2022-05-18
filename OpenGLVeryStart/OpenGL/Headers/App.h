#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <ResourceManager.h>
#include <Model.h>
#include <Maths.h>
#include <Camera.h>

namespace Core
{
	struct AppInitializer
	{
		unsigned int width;
		unsigned int height;
		unsigned int major;
		unsigned int minor;
		const char* name;
		void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height);
		void (*glDebugOutput)(GLenum source, GLenum type, GLuint id, GLenum severity,GLsizei length, const GLchar* message, const void* userParam);
	};

	class App
	{
	private:

	public:
		GLFWwindow* window;
		LowRenderer::Camera cam;
	private:

	public:
		App()
		{
			cam = LowRenderer::Camera();
		}

		~App();

		void Init(AppInitializer intializer);
		void Update(int shaderProgram, unsigned int VAO);
		void processInput();
	};
}