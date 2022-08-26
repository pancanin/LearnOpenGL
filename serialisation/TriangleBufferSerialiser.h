#pragma once
#include "BufferSerialiser.h"

class TriangleBufferSerialiser :
    public BufferSerialiser
{
public:
	float* serialise() const;
	unsigned int size() const;
private:
	unsigned int floatsPerTriangle = 9;
};
