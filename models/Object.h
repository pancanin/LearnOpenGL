#pragma once

class Object {
public:
	virtual float* toVertexArray(int& outSize) const = 0;
};