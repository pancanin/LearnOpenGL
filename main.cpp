#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ui/Window.h"
#include "graphics/Graphics.h"
#include "input/KeyboardInput.h"

#include "utils/ShaderLoader.h"
#include "graphics/ShaderProgram.h"

#include "graphics/VertexArrayObject.h"
#include "graphics/VertexBufferObject.h"

#include "models/TypeDefs.h"
#include "models/Triangle.h"
#include "models/Rect.h"
#include "models/ColorTriangle.h"
#include "models/Vertex.h"

#include "graphics/ObjectComponent.h"
#include "models/VertexAttribute.h"

#include "models/TexturedTriangle.h"

#include "utils/TextureComponent.h"
#include "graphics/RectComponent.h"

#include "arcanoid/Arcanoid.h"

const int width = 800;
const int height = 600;

int main() {
	Arcanoid arcanoidGame;
	arcanoidGame.start();

	return 0;
}