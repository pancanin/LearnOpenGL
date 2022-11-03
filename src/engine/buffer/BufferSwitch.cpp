#include "BufferSwitch.h"

#include "../../opengl/models/TriangleVertex.h"

void BufferSwitch::init()
{
	std::vector<VertexAttribute> attributes = {
		VertexAttribute{ 0, sizeof(TriangleVertex::position) / sizeof(float), sizeof(TriangleVertex) / sizeof(float), 0 },
		VertexAttribute{ 1, sizeof(TriangleVertex::normal) / sizeof(float), sizeof(TriangleVertex) / sizeof(float), offsetof(TriangleVertex, TriangleVertex::normal) / sizeof(float) },
		VertexAttribute{ 2, sizeof(TriangleVertex::textureCoords) / sizeof(float), sizeof(TriangleVertex) / sizeof(float), offsetof(TriangleVertex, TriangleVertex::textureCoords) / sizeof(float) },
		VertexAttribute{ 3, sizeof(TriangleVertex::idx) / sizeof(float), sizeof(TriangleVertex) / sizeof(float), offsetof(TriangleVertex, TriangleVertex::idx) / sizeof(float) }
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

	std::vector<VertexAttribute> lineAttrs = {
		VertexAttribute{ 0, sizeof(LineVertex::position) / sizeof(float), sizeof(LineVertex) / sizeof(float), 0 },
		VertexAttribute{ 1, sizeof(LineVertex::isEnd) / sizeof(float), sizeof(LineVertex) / sizeof(float), offsetof(LineVertex, LineVertex::isEnd) / sizeof(float) },
	};

	lineSerialiserPtr = std::make_shared<LineBufferSerialiser>();
	lineBufferConfigurer.init(lineAttrs, lineSerialiserPtr);
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
