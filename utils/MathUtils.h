#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "../libs/glm/glm.hpp"

namespace MathUtils {
	/* Given a point in 3D space, builds a square with size squareSize with the point in the center.
	* Expects screen coordiantes and returns screen coordinates.
	*/
	inline glm::vec4 calculateSquareAtPoint(glm::vec3 point, float squareSize) {
		float halfSize = squareSize / 2;
		float upperLeftX = point.x - halfSize;
		float upperLeftY = point.y - halfSize;
		float lowerRightX = point.x + halfSize;
		float lowerRightY = point.y + halfSize;

		return glm::vec4(upperLeftX, upperLeftY, lowerRightX, lowerRightY);
	}

	/*
	* rectangle is represented with 4 coordinates - x,y of upper left and x,y of lower right
	*/
	inline bool isPointInRect(glm::vec4 rect, glm::vec3 point) {
		return point.x >= rect.x && point.x <= rect.z && point.y >= rect.y && point.y <= rect.w;
	}

	/*
	* Maps vertex y coordinate from -1.0 to 1.0 to numbers from 0 to screen's height.
	* Because Y axis is flipped, subtract the result from height.
	*/
	inline int mapVertexYToScreenY(float y, int screenHeight) {
		float normalized = (y + 1) / 2;

		return screenHeight - normalized * screenHeight;
	}

	/*
	* Maps vertex x coordinate from -1.0 to 1.0 to numbers from 0 to screen's width.
	*/
	inline int mapVertexXToScreenX(float x, int screenWidth) {
		float normalized = (x + 1) / 2;

		return normalized * screenWidth;
	}

	inline glm::vec3 mapVertexToScreen(glm::vec3 vertex, int windowWidth, int windowHeight) {
		return glm::vec3(
			mapVertexXToScreenX(vertex.x, windowWidth),
			mapVertexYToScreenY(vertex.y, windowHeight),
			0.0f
		);
	}

	/*
	* Maps screen coordinates from 0 to max to vertex coordinates from -1 to 1.
	*/
	inline float mapToVertexCoordinates(float value, float max) {
		float normalized = value / max;

		return (normalized + normalized) - 1;
	}

	inline float mapScreenXToVertexX(float x, float maxWidth) {
		float normalized = x / maxWidth;

		return (normalized + normalized) - 1;
	}

	inline float mapScreenYToVertexY(float y, float maxHeight) {
		float normalized = y / maxHeight;

		return -(normalized + normalized - 1);
	}

	inline glm::vec3 mapScreenToVertexCoordinates(glm::vec3 screen, unsigned int maxWidth, unsigned int maxHeight) {
		return glm::vec3(mapScreenXToVertexX(screen.x, maxWidth), mapScreenYToVertexY(screen.y, maxHeight), 0.0f);
	}

	inline float triangleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
		glm::vec3 ab = b - a;
		glm::vec3 ac = c - a;
		float area = glm::length(glm::cross(ab, ac));

		return area / 2;
	}

	inline bool isPointInTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 p) {
		float outerTriangleArea = triangleArea(a, b, c);

		float abpArea = triangleArea(p, a, b);
		float bpcArea = triangleArea(p, b, c);
		float apcArea = triangleArea(p, c, a);

		return abpArea + bpcArea + apcArea == outerTriangleArea;
	}

	inline bool isPointInRect(glm::vec3 diagonalPointA, glm::vec3 diagonalPointB, glm::vec3 point) {
		return (diagonalPointA.x <= point.x && diagonalPointA.y <= point.y && diagonalPointB.x >= point.x && diagonalPointB.y >= point.y) ||
			(diagonalPointA.x >= point.x && diagonalPointA.y >= point.y && diagonalPointB.x <= point.x && diagonalPointB.y <= point.y);
	}
};