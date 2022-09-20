#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "libs/stb_image.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include "examples/pleven-mafia-wars/Chistkata.h"


int main()
{
	Chistkata chistkataGame;
	chistkataGame.init();
	chistkataGame.start();

	return 0;
}
