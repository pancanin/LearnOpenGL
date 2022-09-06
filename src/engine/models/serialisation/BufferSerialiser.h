#pragma once

class BufferSerialiser {
public:
	virtual float* serialise() const = 0;

	/* The number of floating point values that are associated with one object. */
	virtual unsigned int size() const = 0;
};
