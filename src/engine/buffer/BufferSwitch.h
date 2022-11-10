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
	BufferConfigurer triangleBufferConfig;
	BufferConfigurer rectBufferConfig;
	BufferConfigurer cubeBufferConfigurer;
	BufferConfigurer lineBufferConfigurer;
	BufferConfigurer pointBufferConfigurer;
	std::shared_ptr<TriangleBufferSerialiser> triangleSerialiserPtr;
	std::shared_ptr<RectBufferSerialiser> rectSerialiserPtr;
	std::shared_ptr<CubeBufferSerialiser> cubeSerialiserPtr;
	std::shared_ptr<LineBufferSerialiser> lineSerialiserPtr;
	std::shared_ptr<PointBufferSerialiser> pointSerialiserPtr;
};