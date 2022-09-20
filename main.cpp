#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "libs/stb_image.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include "src/engine/ui/Window.h"
#include "src/opengl/shader/ShaderProgram.h"
#include "src/engine/core/Graphics.h"
#include "src/engine/camera/FPSCamera.h"
#include "src/opengl/buffers/BufferConfigurer.h"
#include "src/engine/models/serialisation/TriangleBufferSerialiser.h"

#include "src/opengl/vbo/VertexBufferObject.h"
#include "src/opengl/vao/VertexArrayObject.h"
#include "src/opengl/texture/TextureComponent.h"
#include "src/opengl/models/Vertex.h"
#include "src/engine/storage/BagOfObjects.h"
#include "src/engine/storage/BagOfLines.h"
#include "src/engine/models/Object.h"
#include "src/engine/core/PhysicsSystem.h"

#include <iostream>
#include <string>

using namespace std;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	
}

FPSCamera cam;

int main()
{
	Graphics g;
	g.init();
	
	cam.init(glm::radians(45.0f), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f, Point3D(0.0f, 0.0f, -3.0f), Point3D(0.0f), SCR_WIDTH, SCR_HEIGHT);
	// glfw window creation
	// --------------------
	Window window;
	window.init(SCR_WIDTH, SCR_HEIGHT, "Learning Open GL", Color(0.2f, 0.2f, 0.2f, 1.0f));
	window.makeActive();
	window.registerCursorPositionCallback(mouse_callback);
	window.registerMouseButtonCallback(mouse_button_callback);
	window.disableCursor();

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!g.loadFunctionDefinitions())
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	ShaderProgram defaultShader;
	defaultShader.init();
	defaultShader.attachVertexShader("src/engine/shaders/default_vertex");
	defaultShader.attachFragmentShader("src/engine/shaders/default_fragment");
	defaultShader.link();
	defaultShader.use();

	TextureComponent texture;
	texture.init(GL_TEXTURE0);
	texture.load("assets/container.jpg");
	texture.bind();

	TextureComponent texture2;
	texture2.init(GL_TEXTURE1);
	texture2.load("assets/wall.jpg");
	texture2.bind();


	// Create triangle the new way.
	BagOfObjects bag;
	bag.init(100);

	Object triangle;
	triangle.position = glm::vec3(0.0f, 0.0f, 0.0f);
	triangle.rotationAxis = glm::vec3(1.0f);
	triangle.velocity = glm::vec3(0.0f);
	triangle.type = ObjectType::TRIANGLE;
	triangle.textureUnit = 0;

	//bag.add(triangle);

	Object triangle2;
	triangle2.position = glm::vec3(0.0f, 0.1f, 0.1f);
	triangle2.rotationAxis = glm::vec3(1.0f);
	triangle2.velocity = glm::vec3(0.0f);
	triangle2.type = ObjectType::TRIANGLE;
	triangle2.textureUnit = 1;

	//bag.add(triangle2);

	Object floor;
	floor.position = glm::vec3(1.0f, 0.2f, 0.0f);
	floor.rotationAxis = glm::vec3(1.0f);
	floor.velocity = glm::vec3(0.0f);
	floor.type = ObjectType::RECT;
	floor.textureUnit = 0;

	//bag.add(floor);

	Object cube1;
	cube1.position = glm::vec3(-1.0f, -0.2f, 0.0f);
	cube1.rotationAxis = glm::vec3(1.0f);
	cube1.velocity = glm::vec3(0.0f);
	cube1.type = ObjectType::CUBE;
	cube1.textureUnit = 1;

	bag.add(cube1);

	BagOfLines bagLines;
	bagLines.init(100);

	Line line;
	line.start = cam.getPosition();
	line.end = Vector3D(0.0f, 0.0f, 100.0f);
	line.color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	Line& realLine = bagLines.add(line);

	PhysicsSystem physics;

	

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// render loop
	// -----------
	while (!window.shouldClose())
	{
		processInput(window.getRaw());

		window.clear();

		texture.bind();
		texture2.bind();

		realLine.start = cam.getPosition() + Vector3D(0.0f, -0.2f, 0.0f);
		realLine.end =  cam.getPosition() + cam.getFront() * 1000.0f;

		physics.checkCollisions(bagLines, bag);

		// Put a cap on how many intersections we process per frame
		while (!physics.intersectionPoints.empty()) {
			Point3D point = physics.intersectionPoints.front();
			physics.intersectionPoints.pop();

			Object explosion;
			explosion.position = point;
			explosion.rotationAxis = glm::vec3(1.0f);
			explosion.velocity = glm::vec3(0.0f);
			explosion.scaleFactor = glm::vec3(0.05f, 0.05f, 0.05f);
			explosion.type = ObjectType::CUBE;
			explosion.textureUnit = 1;
			explosion.intersectible = false;

			bag.add(explosion);
		}

		bagLines.draw(cam);
		bag.draw(cam);
		
		window.swapBuffers();
		g.pollEvents();
	}

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam.moveForward();
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam.moveBackward();
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam.moveLeft();
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam.moveRight();
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	cam.onMouseMove(xpos, ypos);
}