#pragma once

#include <vector>

#include "../models/VertexAttribute.h"

class AttributeConfigurer {
public:
	virtual std::vector<VertexAttribute> getAttributes() const = 0;
	
protected:
	//void add(const VertexAttribute&);
private:
	unsigned int currentAttrIndex;
	unsigned int currentStride;
};