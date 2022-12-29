#pragma once

#include <memory>

#include "../models/ObjectType.h"
#include "../models/serialisation/BufferSerialiser.h"
#include "../../opengl/buffers/BufferConfigurer.h"
#include "../models/serialisation/TriangleBufferSerialiser.h"
#include "../models/serialisation/RectBufferSerialiser.h"
#include "../models/serialisation/CubeBufferSerialiser.h"
#include "../models/serialisation/LineBufferSerialiser.h"
#include "../models/serialisation/PointBufferSerialiser.h"

class BufferSwitch {
public:
	void init();

	std::shared_ptr<BufferSerialiser> switchBuffer(ObjectType type);
private:
	const static uint32_t objectTypesCount = 5;
	BufferConfigurer configurations[objectTypesCount];
	std::shared_ptr<BufferSerialiser> serialisers[objectTypesCount];
};