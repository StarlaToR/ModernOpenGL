#pragma once
#include <Maths.h>

namespace LowRenderer
{
	class Camera
	{
	private:
		float f = 100.f;
		float n = 1.f;
		float fov = 45;
		float s = 1 / tanf((fov / 2) * (M_PI / 180));;
		float c = f / (f - n);

		Mat4 transformMatrix = GetIdentityMat4();
		Mat4 viewMatrix = GetIdentityMat4();

		Mat4 projectionMatrix = {
		s, 0.f, 0.f, 0.f,
		0.f, s, 0.f, 0.f,
		0.f, 0.f, -c, -(c * n),
		0.f, 0.f, -1.f, 0.f,
		};	

	public:
		Vec3 direction;
		Vec3 target = Vec3();
		Vec3 position = Vec3(0, 0, -9);
		Vec3 rotation;
		Vec3 camUp;
		Vec3 camRight = Vec3();
		float speed = 0.05f;

		Camera() {}
		~Camera() {}

		void Update();
		Mat4 GetViewMatrix() { return viewMatrix; };
		Mat4 GetProjectionMatrix() { return projectionMatrix; };
		Mat4 LookAt(const Vec3& targ);

	};
}