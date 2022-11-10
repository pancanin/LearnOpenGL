#include "BufferSwitch.h"

#include "../../opengl/models/Vertex.h"

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

	std::vector<VertexAttribute> lineAttrs = {
		VertexAttribute{ 0, sizeof(LineVertex::position) / sizeof(float), sizeof(LineVertex) / sizeof(float), 0 },
	};

	lineSerialiserPtr = std::make_shared<LineBufferSerialiser>();
	lineBufferConfigurer.init(lineAttrs, lineSerialiserPtr);
	lineBufferConfigurer.activate();
	lineBufferConfigurer.loadBuffer();

	pointSerialiserPtr = std::make_shared<PointBufferSerialiser>();
	// Reusing lineAttrs here but this might break if Line attributes change.
	pointBufferConfigurer.init(lineAttrs, pointSerialiserPtr);
	pointBufferConfigurer.activate();
	pointBufferConfigurer.loadBuffer();
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
	case ObjectType::POINT:
		pointBufferConfigurer.activate();
		return pointSerialiserPtr;
	}

	return nullptr;
}
