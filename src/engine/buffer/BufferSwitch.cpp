#include "BufferSwitch.h"

void BufferSwitch::init()
{
	configurations[(size_t)ObjectType::TRIANGLE].init(
		serialisers[(size_t)ObjectType::TRIANGLE] = std::make_shared<TriangleBufferSerialiser>()
	);

	configurations[(size_t)ObjectType::RECT].init(
		serialisers[(size_t)ObjectType::RECT] = std::make_shared<RectBufferSerialiser>()
	);

	// TODO: Finish this off
	configurations[(size_t)ObjectType::CUBE].init(
		serialisers[(size_t)ObjectType::TRIANGLE] = std::make_shared<TriangleBufferSerialiser>()
	);

	configurations[(size_t)ObjectType::TRIANGLE].init(
		serialisers[(size_t)ObjectType::TRIANGLE] = std::make_shared<TriangleBufferSerialiser>()
	);

	triangleSerialiserPtr = std::make_shared<TriangleBufferSerialiser>();
	triangleBufferConfig.init(triangleSerialiserPtr);

	rectSerialiserPtr = std::make_shared<RectBufferSerialiser>();
	rectBufferConfig.init(rectSerialiserPtr);

	cubeSerialiserPtr = std::make_shared<CubeBufferSerialiser>();
	cubeBufferConfigurer.init(cubeSerialiserPtr);

	lineSerialiserPtr = std::make_shared<LineBufferSerialiser>();
	lineBufferConfigurer.init(lineSerialiserPtr);
}

std::shared_ptr<BufferSerialiser> BufferSwitch::switchBuffer(ObjectType type)
{
	switch (type) {
	case ObjectType::TRIANGLE:
		triangleBufferConfig.activate();
		return triangleSerialiserPtr;
	case ObjectType::RECT:
		rectBufferConfig.activate();
		return rectSerialiserPtr;
	case ObjectType::CUBE:
		cubeBufferConfigurer.activate();
		return cubeSerialiserPtr;
	case ObjectType::LINE:
		lineBufferConfigurer.activate();
		return lineSerialiserPtr;
	}

	return nullptr;
}
