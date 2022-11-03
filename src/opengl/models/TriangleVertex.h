#pragma once

#include "Vertex.h"

struct TriangleVertex : Vertex {
	/// <summary>
	/// Marks a vertex with a number, usually 0,1,2 and it will represent the index of that vertex in
	/// the triangle.
	/// Note: It is a float, because the buffer that we are using is a float buffer.
	/// One application of this field is to know which vertex we are processing and to transform it 
	/// based on the coordinates of each point of the triangle.
	/// </summary>
	float idx;
};
