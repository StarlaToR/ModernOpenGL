#pragma once
#include <Model.h>
#include <Math.h>
#include <Texture.h>

using namespace Resources;

namespace LowRenderer
{
	class Mesh
	{
	private:
		unsigned int VBO, VAO, EBO;
		Model* model;
		Mat4 modelMatrix;
		Texture* texture;
	public:
		Mesh(Model* mod, const Mat4& mat, Texture* text);
		~Mesh();
		
		void Update(const Mat4& projviewMatrix, unsigned int shaderProgram);
	};
}