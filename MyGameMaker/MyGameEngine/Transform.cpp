#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>


Transform::Transform(const mat4& mat) : _mat(mat)
{
	_rot = glm::quat_cast(_mat);
	_scale = glm::vec3(glm::length(_mat[0]), glm::length(_mat[1]), glm::length(_mat[2]));
}

void Transform::rotate(const vec3& eulerAngles) 
{
	vec3 currentTransform = _mat[3]; // Translation is stored in the last column
	vec3 currentScale = glm::vec3(glm::length(_mat[0]), glm::length(_mat[1]), glm::length(_mat[2])); // Scale is the length of the columns;

	_rot = glm::quat(eulerAngles);
	_mat = glm::mat4(1.0f);

	_mat[0] = glm::vec4(currentScale.x, 0.0f, 0.0f, 0.0f);
	_mat[1] = glm::vec4(0.0f, currentScale.y, 0.0f, 0.0f);
	_mat[2] = glm::vec4(0.0f, 0.0f, currentScale.z, 0.0f);

	_mat = mat4(glm::mat4_cast(_rot)) * _mat;
	_mat[3] = glm::vec4(currentTransform, 1.0f);
}