#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <ResourceManager.h>
#include <Maths.h>
#include <Camera.h>
#include <Mesh.h>
#include <Light.h>
#include <Log.h>
#include <sstream>

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
		std::vector<LowRenderer::Mesh*> meshes;
		std::vector<LowRenderer::PointLight*> pointLights;
		std::vector<LowRenderer::DirectionnalLight*> directLights;
		std::vector<LowRenderer::SpotLight*> spotLights;

		App()
		{
			cam = LowRenderer::Camera();
		}

		~App();

		void Init(AppInitializer intializer);
		void Update(unsigned int shaderProgram);
		void PointLightsToShaders(unsigned int shaderProgram);
		void DirectLightsToShaders(unsigned int shaderProgram);
		void SpotLightsToShaders(unsigned int shaderProgram);
		void processInput();
	};
}