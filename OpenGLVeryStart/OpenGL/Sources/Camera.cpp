#include <Camera.h>

using namespace LowRenderer;

void Camera::Update()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    speed = deltaTime * 5.f;

	viewMatrix = LookAt();
}

Mat4 Camera::LookAt(const Vec3& targ)
{
    camForward = (position + targ).GetNormalizedVector();
    camRight = GetCrossProduct(Vec3(0, 1, 0), camForward).GetNormalizedVector();
    camUp = GetCrossProduct(camForward, camRight);

    Mat4 mat = Mat4(camRight.x, camRight.y, camRight.z, -GetDotProduct(camRight, position),
					camUp.x, camUp.y, camUp.z, -GetDotProduct(camUp, position),
					camForward.x, camForward.y, camForward.z, -GetDotProduct(camForward, position),
					0, 0, 0, 1);

    return mat;
}

Mat4 Camera::LookAt()
{
	camRight = GetCrossProduct(Vec3(0, 1, 0), camForward).GetNormalizedVector();
	camUp = GetCrossProduct(camForward, camRight);

	Mat4 mat = Mat4(camRight.x, camRight.y, camRight.z, -GetDotProduct(camRight, position),
		camUp.x, camUp.y, camUp.z, -GetDotProduct(camUp, position),
		camForward.x, camForward.y, camForward.z, -GetDotProduct(camForward, position),
		0, 0, 0, 1);

	return mat;
}

void Camera::MouseDirection(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	
	float sensitivity = 0.2f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	Vec3 dir = {
		cos(DegToRad(yaw))* cos(DegToRad(pitch)),
		-sin(DegToRad(pitch)),
		sin(DegToRad(yaw))* cos(DegToRad(pitch)),
		};
	camForward = dir.GetNormalizedVector();
	oldDirection = camForward;
}

/*
void Camera::ShowImGuiControls()
{
    ImGui::Text("Test");
}
*/