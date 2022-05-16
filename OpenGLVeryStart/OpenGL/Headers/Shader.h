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
		unsigned int vertexShader;
		unsigned int fragmentShader;
		int success;
		char infoLog[512];
	public:
		unsigned int shaderProgram;

		Shader(const char* vertexPath, const char* fragmentPath)
		{
			SetVertexShader(vertexPath);
			SetFragmentShader(fragmentPath);
			Link();
		}

		bool SetVertexShader(const char* filename);
		bool SetFragmentShader(const char* filename);
		bool Link();
	};
}