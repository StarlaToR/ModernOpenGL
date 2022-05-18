#include <Camera.h>

using namespace LowRenderer;

void Camera::Update()
{
    direction = (position - target).GetNormalizedVector();
    camRight = GetCrossProduct(Vec3(0,1,0), direction).GetNormalizedVector();
    camUp = GetCrossProduct(direction, camRight);

    transformMatrix = CreateTransformMatrix(position, rotation, { 1,1,1 });
    viewMatrix = transformMatrix.GetInvertibleMat4();
}

Mat4 Camera::LookAt(const Vec3& targ)
{
    direction = (position - target).GetNormalizedVector();
    camRight = GetCrossProduct(Vec3(0, 1, 0), direction).GetNormalizedVector();
    camUp = GetCrossProduct(direction, camRight);

    Mat4 mat1 = Mat4(camRight.x, camRight.y, camRight.z, 0, camUp.x, camUp.y, camUp.z, 0, direction.x, direction.y, direction.z, 0, 0, 0, 0, 1);
    Mat4 mat2 = Mat4(1, 0, 0, -position.x, 0, 1, 0, -position.y, 0, 0, 1, -position.z, 0, 0, 0, 1);

    return mat1 * mat2;
}

/*
void Camera::ShowImGuiControls()
{
    ImGui::Text("Test");
}
*/