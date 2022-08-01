#pragma once

class Object {
public:
	virtual float* toVertexArray(unsigned int& outSize) const = 0;
};