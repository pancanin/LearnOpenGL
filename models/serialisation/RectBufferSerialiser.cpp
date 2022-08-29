#include "RectBufferSerialiser.h"

float* RectBufferSerialiser::serialise() const
{
	float* arr = new float[size()];

	// TODO: Add valid array buffer

	return arr;
}

unsigned int RectBufferSerialiser::size() const
{
	return 20;
}
