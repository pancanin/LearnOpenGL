#pragma once

#include "../../src/engine/Engine.h"

class Chistkata : public Engine {
public:
	void onStart();
	void onUpdate();
	void onStop();

	void processInput();
	void onMouseMove(double xpos, double ypos);
private:
	Line* laserBeam;

	void activateLaser();
	void updateLaserPos();
	void deactivateLaser();
};