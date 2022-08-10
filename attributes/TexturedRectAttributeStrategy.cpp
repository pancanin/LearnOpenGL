#include "TexturedRectAttributeStrategy.h"

std::vector<VertexAttribute> TexturedRectAttributeStrategy::getAttributes() const
{
	return std::vector<VertexAttribute> {
		VertexAttribute(0, 3, 6, 0),
			VertexAttribute(1, 2, 6, 3),
			VertexAttribute(2, 1, 6, 5)
	};
}
