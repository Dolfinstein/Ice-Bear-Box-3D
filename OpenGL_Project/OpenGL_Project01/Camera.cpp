#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position); // ��L���ܦ����V�q�ҥH��normalize
	Right = glm::normalize(glm::cross(Forward, WorldUp)); // ���V�ؼЪ���V��@�ɦV�W����V�i�Hcross�X��v�����k���V
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
	Right = glm::normalize(glm::cross(Forward, WorldUp)); // ���V�ؼЪ���V��@�ɦV�W����V�i�Hcross�X��v�����k���V
	Up = glm::normalize(glm::cross(Forward, Right));
}
Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUp); // lookAt ��ƥi�H������XView Matrix 
	// �ƾǤW�n��]�O�n�o�ǦV�q�Ӳզ��x�}
}

void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp)); // ���V�ؼЪ���V��@�ɦV�W����V�i�Hcross�X��v�����k���V
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