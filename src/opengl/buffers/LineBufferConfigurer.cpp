#include "LineBufferConfigurer.h"

void LineBufferConfigurer::init(std::vector<VertexAttribute> attributes, std::shared_ptr<LineBufferSerialiser> serialisation)
{
	BufferConfigurer::init(attributes, serialisation);
}

void LineBufferConfigurer::loadBuffer(Point3D start, Point3D end)
{
	float* buffer = serialisationPtr->serialise(start, end);
	vbo.fillBuffer(buffer, serialisationPtr->size());
	delete[] buffer;
}
