#include "BufferSwitch.h"

void BufferSwitch::init()
{
	configurations[(size_t)ObjectType::TRIANGLE].init(
		serialisers[(size_t)ObjectType::TRIANGLE] = std::make_shared<TriangleBufferSerialiser>()
	);

	configurations[(size_t)ObjectType::RECT].init(
		serialisers[(size_t)ObjectType::RECT] = std::make_shared<RectBufferSerialiser>()
	);

	configurations[(size_t)ObjectType::CUBE].init(
		serialisers[(size_t)ObjectType::CUBE] = std::make_shared<CubeBufferSerialiser>()
	);

	configurations[(size_t)ObjectType::LINE].init(
		serialisers[(size_t)ObjectType::LINE] = std::make_shared<LineBufferSerialiser>()
	);

	configurations[(size_t)ObjectType::POINT].init(
		serialisers[(size_t)ObjectType::POINT] = std::make_shared<LineBufferSerialiser>()
	);
}

std::shared_ptr<BufferSerialiser> BufferSwitch::switchBuffer(ObjectType type)
{
	configurations[(size_t)type].activate();

	return serialisers[(size_t)type];
}
