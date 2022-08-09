#include "../engine/Engine.h"

class Arcanoid : public Engine {
private:
	void onStart();
	void onUpdate();
	void onStop();

	const unsigned int screenWidth = 800;
	const unsigned int screenHeight = 600;
	const std::string title = "Arcanoid";
	const Color screenClearColor = Color(4, 44, 98, 255);
};