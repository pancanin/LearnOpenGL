#pragma once
#include <queue>

#include "../models/TypeDefs.h"

class BagOfLines;
class BagOfObjects;
struct Object;
struct Line;

class PhysicsSystem {
public:
	// TODO: It is better to depend on iterators instead of concrete 'Bag' classes but for dev-speed I choose this approach.
	void checkCollisions(const BagOfLines& bagOfLines, const BagOfObjects& bagOfObjects);

	std::queue<Point3D> intersectionPoints;
private:
	bool checkBoxLineCollision(const Object& box, const Line& line);
};
