#ifndef EXAMPLES_BALLKEK
#define EXAMPLES_BALLKEK

#include "../../src/engine/Engine.h"

class Ballkek : public Engine {
public:
	void onStart();
	void onUpdate();
	void onStop();

	void processInput();
	void onMouseMove(double xpos, double ypos);
	void onMouseClick(int button, int action);
};

#endif // !EXAMPLES_BALLKEK
