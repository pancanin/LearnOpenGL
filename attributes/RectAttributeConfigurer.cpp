#include "RectAttributeConfigurer.h"

std::vector<VertexAttribute> RectAttributeConfigurer::getAttributes() const {
	return std::vector<VertexAttribute> {
		VertexAttribute(0, 3, 5, 0),
			VertexAttribute(1, 2, 5, 3)
	};
}