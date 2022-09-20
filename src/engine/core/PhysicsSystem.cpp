#include <iostream>

#include "PhysicsSystem.h"

#include "../storage/BagOfLines.h"
#include "../storage/BagOfObjects.h"

void PhysicsSystem::checkCollisions(const BagOfLines& bagOfLines, const BagOfObjects& bagOfObjects)
{
	for (auto it = bagOfLines.iter_begin(); it != bagOfLines.iter_end(); ++it) {
		const Line& currentLine = *it;

		for (auto oit = bagOfObjects.iter_begin(); oit != bagOfObjects.iter_end(); ++oit) {
			const Object& currentObject = *oit;
			
			if (checkBoxLineCollision(currentObject, currentLine)) {
				
			}
		}
	}
}

bool PhysicsSystem::checkBoxLineCollision(const Object& box, const Line& line)
{
	if (!box.intersectible) { return false; }
	// Calculating the min point and max point of the bounding volume / box.
	float minX = box.position.x - (1 * box.scaleFactor.x);
	float minY = box.position.y - (1 * box.scaleFactor.y);
	float minZ = box.position.z - (1 * box.scaleFactor.z);

	float maxX = box.position.x + (1 * box.scaleFactor.x);
	float maxY = box.position.y + (1 * box.scaleFactor.y);
	float maxZ = box.position.z + (1 * box.scaleFactor.z);

	Point3D collisionInfo;

	Vector3D rayDir = glm::normalize(line.end - line.start);

	float tmin = (minX - line.start.x) / rayDir.x;
	float tmax = (maxX - line.start.x) / rayDir.x;

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (minY - line.start.y) / rayDir.y;
	float tymax = (maxY - line.start.y) / rayDir.y;

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (minZ - line.start.z) / rayDir.z;
	float tzmax = (maxZ - line.start.z) / rayDir.z;

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	Point3D intersectionPoint = line.start + (tmin * rayDir);

	// TODO: Implement a queue class with limit
	intersectionPoints.push(intersectionPoint);
	if (intersectionPoints.size() > 100) {
		intersectionPoints.pop();
	}

	return true;
}
