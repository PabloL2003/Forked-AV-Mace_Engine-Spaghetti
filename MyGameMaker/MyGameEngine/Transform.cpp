#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>


Transform::Transform(const mat4& mat) {
	_mat = glm::mat4_cast(_rot);
}

void Transform::translate(const vec3& v) {
	_mat = glm::translate(_mat,v);
}

void Transform::rotate(const vec3& eulerAngles) 
{
	_rot = glm::quat(eulerAngles);
	_mat = glm::mat4_cast(_rot);
}

void Transform::rotate(double rads, const vec3& v) 
{
	_mat = glm::rotate(_mat, rads, v);
}