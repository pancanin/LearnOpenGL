#include "BufferSwitch.h"

void BufferSwitch::init()
{
	std::vector<VertexAttribute> attributes = {
		VertexAttribute{ 0, sizeof(Vertex::position) / sizeof(float), sizeof(Vertex) / sizeof(float), 0 },
		VertexAttribute{ 1, sizeof(Vertex::normal) / sizeof(float), sizeof(Vertex) / sizeof(float), offsetof(Vertex, Vertex::normal) / sizeof(float) },
		VertexAttribute{ 2, sizeof(Vertex::textureCoords) / sizeof(float), sizeof(Vertex) / sizeof(float), offsetof(Vertex, Vertex::textureCoords) / sizeof(float) }
	};

	triangleSerialiserPtr = std::make_shared<TriangleBufferSerialiser>();

	triangleBufferConfig.init(attributes, triangleSerialiserPtr);
	triangleBufferConfig.activate();
	triangleBufferConfig.loadBuffer();

	rectSerialiserPtr = std::make_shared<RectBufferSerialiser>();

	rectBufferConfig.init(attributes, rectSerialiserPtr);
	rectBufferConfig.activate();
	rectBufferConfig.loadBuffer();

	cubeSerialiserPtr = std::make_shared<CubeBufferSerialiser>();
	cubeBufferConfigurer.init(attributes, cubeSerialiserPtr);
	cubeBufferConfigurer.activate();
	cubeBufferConfigurer.loadBuffer();

	lineSerialiserPtr = std::make_shared<LineBufferSerialiser>();
	lineBufferConfigurer.init(attributes, lineSerialiserPtr);
	lineBufferConfigurer.activate();
	lineBufferConfigurer.loadBuffer();
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
