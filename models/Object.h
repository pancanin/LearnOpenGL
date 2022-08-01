#pragma once

class Object {
public:
	virtual float* toVertexArray() const = 0;
	virtual unsigned int getComponentsCount() const = 0;
};