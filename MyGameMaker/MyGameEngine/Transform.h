#pragma once

#include "types.h"
#include "Component.h"

class Transform : public Component 
{
	union {
		mat4 _mat = mat4(1.0);
		struct {
			vec3 _left; mat4::value_type _left_w;
			vec3 _up; mat4::value_type _up_w;
			vec3 _fwd; mat4::value_type _fwd_w;
			vec3 _pos; mat4::value_type _pos_w;
		};
	};

	glm::quat _rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f);    

public:
	const mat4 mat() const { return _mat; }
	const vec3 left() const { return _left; }
	const vec3 right() const { return _left; }
	const vec3 up() const { return _up; }
	const vec3 fwd() const { return _fwd; }

	//Position
	vec3& pos() { return _pos; }
	const vec3& pos() const { return _pos; }

	//Rotation
	glm::quat rot() const { return _rot; }
	vec3 eulerAngles() const { return glm::eulerAngles(_rot); }

	//Scale
	const glm::vec3& scale() const { return _scale; }
	glm::vec3& scale() { return _scale; }

	void setFwd(const vec3& fwd) { _fwd = fwd; }
	void setRigth(const vec3& left) { _left = left; }
	void setUp(const vec3& up) { _up = up; }

	const auto* data() const { return &_mat[0][0]; }

	void translate(const vec3& v);
	void rotate(const vec3& eulerAngles);
	void rotate(double rads, const vec3& v);

	Transform() = default;
	Transform(const mat4& mat);
	Transform(bool active, GameObject* owner, const mat4& mat) : _mat(mat), Component(active, owner) {}
	Transform operator*(const mat4& other) { return Transform(_mat * other); }
	Transform operator*(const Transform& other) { return Transform(_mat * other._mat); }
};

inline Transform operator*(const mat4& m, const Transform& t) { return Transform(m * t.mat()); }