#pragma once
#include <Maths.h>
#include <GLFW/glfw3.h>
#include <iostream>


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

		float lastX = 400.f, lastY = 300.f, yaw = -90, pitch = 0;

	public:
		Vec3 direction = Vec3();
		Vec3 oldDirection = Vec3(0, 0, -1);
		Vec3 target = Vec3();
		Vec3 position = Vec3(0, 0, -9);
		Vec3 rotation;
		Vec3 camUp;
		Vec3 camRight = Vec3();
		Vec3 camForward = Vec3();
		float speed = 0.05f;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		bool firstMouse = true;

		Camera() {}
		~Camera() {}

		void Update();
		Mat4 GetViewMatrix() { return viewMatrix; };
		Mat4 GetProjectionMatrix() { return projectionMatrix; };
		Mat4 LookAt(const Vec3& targ);
		Mat4 LookAt();
		void MouseDirection(double xpos, double ypos);
	};
}