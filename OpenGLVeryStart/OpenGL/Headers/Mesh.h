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
		Vec3 positionVec;
		Vec3 scaleVec;
		Vec3 rotationVec;
		Texture* texture;
	public:
		float* rotation;
		float* position;
		float* scale;

		Mesh(Model* mod, const Vec3& pos, const Vec3& rot, const Vec3& sca, Texture* text);
		~Mesh();

		void Update(const Mat4& projviewMatrix, unsigned int shaderProgram);
		Mat4 GetModelMatrix();
		void SetPosition(Vec3 pos);
		void SetRotation(Vec3 rot);
		void SetScale(Vec3 sca);
	};
}