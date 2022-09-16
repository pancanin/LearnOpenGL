#pragma once

#include "../../engine/models/TypeDefs.h"
#include "../../engine/models/serialisation/LineBufferSerialiser.h"
#include "BufferConfigurer.h"

class LineBufferConfigurer : public BufferConfigurer {
public:
	void init(
		std::vector<VertexAttribute> attributes,
		std::shared_ptr<LineBufferSerialiser> serialisation
	);

	void loadBuffer(Point3D start, Point3D end);
private:
	std::shared_ptr<LineBufferSerialiser> serialisationPtr;
};