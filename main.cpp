#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "libs/stb_image.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include "examples/ballkek/Ballkek.h"


int main()
{
	Ballkek game;
	game.init();
	game.start();

	return 0;
}
