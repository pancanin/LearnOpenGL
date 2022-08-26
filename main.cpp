#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "libs/stb_image.h"

#include "ui/Window.h"
#include "graphics/ShaderProgram.h"
#include "models/Triangle.h"
#include "utils/MathUtils.h"
#include "graphics/Graphics.h"
#include "utils/TextureComponent.h"
#include "graphics/VertexArrayObject.h"
#include "graphics/VertexBufferObject.h"
#include "engine/FPSCamera.h"
#include "graphics/BufferConfigurer.h"
#include "serialisation/TriangleBufferSerialiser.h"

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
	window.init(SCR_WIDTH, SCR_HEIGHT, "Learning Open GL", Color(0.30f, 0.40f, 0.0f, 1.0f));
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

	ShaderProgram lightSourceShaderProgram;
	lightSourceShaderProgram.init();
	lightSourceShaderProgram.attachVertexShader("texture_vertex");
	lightSourceShaderProgram.attachFragmentShader("light_fragment");
	lightSourceShaderProgram.link();

	ShaderProgram shinedUponShaderProgram;
	shinedUponShaderProgram.init();
	shinedUponShaderProgram.attachVertexShader("texture_vertex");
	shinedUponShaderProgram.attachFragmentShader("shined_upon");
	shinedUponShaderProgram.link();

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	VertexBufferObject vbo;
	vbo.init(GL_ARRAY_BUFFER);
	vbo.bind();
	vbo.fillBuffer(vertices, sizeof(vertices));

	VertexArrayObject vao;
	vao.init();
	vao.bind();
	vao.addAttribute(VertexAttribute{ 0, 3, 6, 0 });
	vao.addAttribute(VertexAttribute{ 1, 3, 6, 3 });

	auto serialiserPtr = std::make_shared<TriangleBufferSerialiser>();
	std::vector<VertexAttribute> triangleAtris = { VertexAttribute{0, 3, 3, 0} };
	BufferConfigurer bufferConfig;
	bufferConfig.init(triangleAtris, serialiserPtr);
	bufferConfig.activate();
	bufferConfig.loadBuffer();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	// render loop
	// -----------
	while (!window.shouldClose())
	{
		processInput(window.getRaw());

		window.clear();

		lightSourceShaderProgram.use();

		lightSourceShaderProgram.setUniformMat4("view", cam.getView());
		lightSourceShaderProgram.setUniformMat4("projection", cam.getProjection());

		vao.bind();
		// create transformations
		glm::mat4 lightModel = glm::mat4(1.0f);
		float radius = 50.0f;
		float time = (float)glfwGetTime();
		auto lightPos = glm::vec3(radius * cos(time), 0.0f, radius * sin(time));
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		lightModel = glm::translate(lightModel, lightPos);

		// Drawing the light source

		auto lightColor = glm::vec3(1.0f);

		lightSourceShaderProgram.setUniformMat4("model", lightModel);
		lightSourceShaderProgram.setUniformVec3("lightColor", lightColor);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Drawing the object that we will shine upon.
		shinedUponShaderProgram.use();
		shinedUponShaderProgram.setUniformMat4("view", cam.getView());
		shinedUponShaderProgram.setUniformMat4("projection", cam.getProjection());
		
		glm::mat4 objectModel = glm::mat4(1.0f);
		objectModel = glm::translate(objectModel, glm::vec3(5.0f, -2.0f, 0.0f));
		
		
		shinedUponShaderProgram.setUniformVec3("objectColor", glm::vec3(0.77f, 0.33f, 0.03f));
		shinedUponShaderProgram.setUniformVec3("lightColor", lightColor);
		shinedUponShaderProgram.setUniformVec3("lightPos", lightPos);
		shinedUponShaderProgram.setUniformVec3("viewerPos", Point3D(0.0f, 0.0f, -3.0f));
		objectModel = glm::scale(objectModel, glm::vec3(5.0f));
		shinedUponShaderProgram.setUniformMat4("model", objectModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		objectModel = glm::translate(objectModel, glm::vec3(-5.0f, -2.0f, 0.0f));
		shinedUponShaderProgram.setUniformMat4("model", objectModel);
		bufferConfig.activate();
		glDrawArrays(GL_TRIANGLES, 0, 3);

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