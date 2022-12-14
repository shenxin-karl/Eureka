#pragma once
#include <string>
#include <variant>

namespace EC {

struct Texture2D {
	std::string defaultTex;
	size_t		slot  = 0;
	size_t		space = 0;
};

struct Color {
	float r = 1.f;
	float g = 1.f;
	float b = 1.f;
	float a = 1.f;
};

struct Range {
	float min = 0.f;
	float max = 1.f;
	float defaultVal = 0.f;
};

struct Vector {
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;
};

using PropertyValue = std::variant<Texture2D, Color, Range, float, Vector, uint32_t, int>;


}
