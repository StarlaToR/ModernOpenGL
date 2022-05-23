#pragma once
#include <Model.h>
#include <Math.h>

using namespace Resources;

namespace LowRenderer
{
	class Mesh
	{
	private:
		unsigned int VBO, VAO, EBO;
		Model* model;
		Mat4 modelMatrix;
	public:
		Mesh(Model* mod, const Mat4& mat);
		~Mesh();
		
		void Update(const Mat4& projviewMatrix, unsigned int shaderProgram);
	};
}