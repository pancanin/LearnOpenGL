#include "RectSerialisationStrategy.h"

float* RectSerialisationStrategy::serialise(const Rect& o) const
{
	float* arr = new float[componentsCountPerObject()];

	arr[0] = o.origin.x;
	arr[1] = o.origin.y;
	arr[2] = o.origin.z;

	arr[3] = 0.0f;
	arr[4] = 1.0f;

	arr[5] = o.origin.x + o.width;
	arr[6] = o.origin.y;
	arr[7] = o.origin.z;

	arr[8] = 1.0f;
	arr[9] = 1.0f;

	arr[10] = o.origin.x + o.width;
	arr[11] = o.origin.y - o.height;
	arr[12] = o.origin.z;

	arr[13] = 1.0f;
	arr[14] = 0.0f;

	arr[15] = o.origin.x;
	arr[16] = o.origin.y - o.height;
	arr[17] = o.origin.z;

	arr[18] = 0.0f;
	arr[19] = 0.0f;

	return arr;
}

unsigned int RectSerialisationStrategy::componentsCountPerObject() const
{
	return 20;
}
