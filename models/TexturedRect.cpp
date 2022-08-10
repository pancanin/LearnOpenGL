#include "TexturedRect.h"

TexturedRect::TexturedRect(unsigned int textureId, Point3D origin, float width, float height) :
	Rect(origin, width, height), textureId(textureId) {}

float* TexturedRect::toVertexArray() const
{
	float* arr = new float[getComponentsCount()];

	arr[0] = origin.x;
	arr[1] = origin.y;
	arr[2] = origin.z;

	arr[3] = 0.0f;
	arr[4] = 1.0f;
	arr[5] = textureId;

	arr[6] = origin.x + width;
	arr[7] = origin.y;
	arr[8] = origin.z;

	arr[9] = 1.0f;
	arr[10] = 1.0f;

	arr[11] = textureId;

	arr[12] = origin.x + width;
	arr[13] = origin.y - height;
	arr[14] = origin.z;

	arr[15] = 1.0f;
	arr[16] = 0.0f;

	arr[17] = textureId;

	arr[18] = origin.x;
	arr[19] = origin.y - height;
	arr[20] = origin.z;

	arr[21] = 0.0f;
	arr[22] = 0.0f;

	arr[23] = textureId;

	return arr;
}
