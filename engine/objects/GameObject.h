#pragma once

#include <memory>

#include "../../models/TypeDefs.h"

template <typename T>
struct GameObject {
	GameObject(std::shared_ptr<T> objectPtr, Point3D position, Point3D direction, float hitPoints, float acceleration) :
		position(position), direction(direction), objectPtr(objectPtr), hitPoints(hitPoints), acceleration(acceleration) {}

	Point3D position;
	Point3D direction;
	std::shared_ptr<T> objectPtr;
	float hitPoints;
	float acceleration;

	void move() {
		this->position += direction * acceleration;
	}

	/*
	* Updates the underlying object based on the changed position vector.
	*/
	virtual void update() = 0;
};