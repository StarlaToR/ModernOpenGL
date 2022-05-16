#pragma once
#define SHADER_H

#include <glad/glad.h>

#include <IResource.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace Resources
{
	class Shader : public IResource
	{
	private:
		unsigned int ID;
		unsigned int vertexShader;
		unsigned int fragmentShader;
		int success;
		char infoLog[512];
	public:
		unsigned int shaderProgram;

		Shader(const char* vertexPath, const char* fragmentPath)
		{
			if (!SetVertexShader(vertexPath))
				std::cout << "Vertex shader not found" << std::endl;
			if (!SetFragmentShader(fragmentPath))
				std::cout << "Fragment shader not found" << std::endl;
			if (Link())
				std::cout << "Shaders can't be binded" << std::endl;
		}

		bool SetVertexShader(const char* filename);
		bool SetFragmentShader(const char* filename);
		bool Link();

		void Use();
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
	};
}