#pragma once

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include <glm/glm.hpp>

using uint = unsigned int;
using mat4 = glm::dmat4;
using vec4 = glm::dvec4;
using vec3 = glm::dvec3;
using vec2 = glm::dvec2;

namespace Colors {
	const glm::u8vec3 Red( 255, 0, 0);
	const glm::u8vec3 Green( 0, 255, 0);
	const glm::u8vec3 Blue( 0, 0, 255);
};

// TYPEDEFS ----------------------------------------------------------------------
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;