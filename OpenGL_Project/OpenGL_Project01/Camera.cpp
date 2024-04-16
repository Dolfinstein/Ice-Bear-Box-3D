#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position); // 把他們變成單位向量所以做normalize
	Right = glm::normalize(glm::cross(Forward, WorldUp)); // 面向目標的方向跟世界向上的方向可以cross出攝影機的右邊方向
	Up = glm::normalize(glm::cross(Forward, Right));


}
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp)); // 面向目標的方向跟世界向上的方向可以cross出攝影機的右邊方向
	Up = glm::normalize(glm::cross(Forward, Right));
}
Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUp); // lookAt 函數可以直接抓出View Matrix 
	// 數學上要抓也是要這些向量來組成矩陣
}

void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp)); // 面向目標的方向跟世界向上的方向可以cross出攝影機的右邊方向
	Up = glm::normalize(glm::cross(Forward, Right));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY * SenseX;
	Yaw -= deltaX * SenseY;
	UpdateCameraVectors();
}


void Camera::UpdateCameraPos()
{
	//Position -= glm::vec3(0, 0, speedZ * 0.03f);
	Position += Forward * 0.03f * speedZ;
	Position += Right * 0.03f * speedLR;
}