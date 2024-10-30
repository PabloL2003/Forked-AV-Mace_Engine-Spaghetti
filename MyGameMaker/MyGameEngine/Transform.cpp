#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

void Transform::translate(const vec3& v) { 
	_mat = glm::translate(_mat,v);
}

void Transform::rotate(double rads, const vec3& v) {
	_mat = glm::rotate(_mat,rads, v);
}

void Transform::rotate(const vec3& eulerAngles) {
	glm::quat quaternion = glm::angleAxis(eulerAngles.x, vec3(1, 0, 0));
	quaternion *= glm::angleAxis(eulerAngles.y, vec3(0, 1, 0));
	quaternion *= glm::angleAxis(eulerAngles.z, vec3(0, 0, 1));

	_mat = glm::translate(glm::mat4(1.0f), (glm::vec3)pos()) * glm::mat4_cast(quaternion) * glm::scale(glm::mat4(1.0f), glm::vec3(1,1,1));

}