#include "TexturedRectBufferSerialiser.h"

float* TexturedRectBufferSerialiser::serialise(const TexturedRect& o) const
{
	float* arr = new float[componentsCountPerObject()];

	arr[0] = o.origin.x;
	arr[1] = o.origin.y;
	arr[2] = o.origin.z;

	arr[3] = 0.0f;
	arr[4] = 1.0f;
	arr[5] = o.textureId;

	arr[6] = o.origin.x + o.width;
	arr[7] = o.origin.y;
	arr[8] = o.origin.z;

	arr[9] = 1.0f;
	arr[10] = 1.0f;

	arr[11] = o.textureId;

	arr[12] = o.origin.x + o.width;
	arr[13] = o.origin.y - o.height;
	arr[14] = o.origin.z;

	arr[15] = 1.0f;
	arr[16] = 0.0f;

	arr[17] = o.textureId;

	arr[18] = o.origin.x;
	arr[19] = o.origin.y - o.height;
	arr[20] = o.origin.z;

	arr[21] = 0.0f;
	arr[22] = 0.0f;

	arr[23] = o.textureId;

	return arr;
}

unsigned int TexturedRectBufferSerialiser::componentsCountPerObject() const
{
	return 24; // TODO: Calculate this
}
