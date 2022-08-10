#pragma once

template <typename T>
class SerialisationStrategy {
public:
	virtual float* serialise(const T& o) const = 0;
	virtual unsigned int componentsCountPerObject() const = 0;
};