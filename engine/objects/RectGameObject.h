#pragma once

#include "../../models/Rect.h"
#include "GameObject.h"

struct RectGameObject : public GameObject<Rect> {
	void update() override {
		this->objectPtr->origin = position;
	}
};