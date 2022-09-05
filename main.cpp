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
#include "models/serialisation/TriangleBufferSerialiser.h"

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

struct PointLight {
	glm::vec3 position;
	glm::vec3 color;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

PointLight ulichniLampi[4];


FPSCamera cam;

int main()
{
	Graphics g;
	g.init();
	
	cam.init(glm::radians(45.0f), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f, Point3D(0.0f, 0.0f, -3.0f), Point3D(0.0f), SCR_WIDTH, SCR_HEIGHT);
	// glfw window creation
	// --------------------
	Window window;
	window.init(SCR_WIDTH, SCR_HEIGHT, "Learning Open GL", Color(0.01f, 0.01f, 0.01f, 1.0f));
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

	TextureComponent container;
	container.init(GL_TEXTURE0);
	container.load("assets/container2.png");

	TextureComponent containerSpecularMap;
	containerSpecularMap.init(GL_TEXTURE1);
	containerSpecularMap.load("assets/cointainer2specularmap.png");

	TextureComponent emmissionMapMatrix;
	emmissionMapMatrix.init(GL_TEXTURE2);
	emmissionMapMatrix.load("assets/matrix-emittance-map.jpg");


	ulichniLampi[0] = PointLight{ glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f, glm::vec3(0.01f), glm::vec3(0.7), glm::vec3(0.9f) };
	ulichniLampi[1] = PointLight{ glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.09f, 0.032f, glm::vec3(0.01f), glm::vec3(0.7), glm::vec3(0.9f) };
	ulichniLampi[2] = PointLight{ glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, 0.09f, 0.032f, glm::vec3(0.01f), glm::vec3(0.7), glm::vec3(0.9f) };

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	VertexBufferObject vbo;
	vbo.init(GL_ARRAY_BUFFER);
	vbo.bind();
	vbo.fillBuffer(vertices, sizeof(vertices));

	VertexArrayObject vao;
	vao.init();
	vao.bind();
	vao.addAttribute(VertexAttribute{ 0, 3, 8, 0 });
	vao.addAttribute(VertexAttribute{ 1, 3, 8, 3 });
	vao.addAttribute(VertexAttribute{ 2, 2, 8, 6 });

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

		// Drawing the object that we will shine upon.
		shinedUponShaderProgram.use();
		container.bind(); // Binding the texture
		containerSpecularMap.bind();
		emmissionMapMatrix.bind();
		
		shinedUponShaderProgram.setUniformMat4("view", cam.getView());
		shinedUponShaderProgram.setUniformMat4("projection", cam.getProjection());
		
		glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		shinedUponShaderProgram.setUniformVec3("objectColor", glm::vec3(0.77f, 0.33f, 0.03f));
		shinedUponShaderProgram.setUniformVec3("viewerPos", cam.getPosition());
		shinedUponShaderProgram.setInt("material.diffuse", 0);
		shinedUponShaderProgram.setInt("material.specular", 1);
		shinedUponShaderProgram.setInt("material.emissive", 2);
		shinedUponShaderProgram.setUniformF("material.shininess", 64.0f);
		
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			shinedUponShaderProgram.setUniformMat4("model", model);


			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// TODO: For multiple lights you have to follow the next tutorial: Probably we have to keep track of several lights as array and 
		// apply the light per each fragment based on all the lights.

		shinedUponShaderProgram.setUniformVec3("theSun.ambient", Point3D(0.1f));
		shinedUponShaderProgram.setUniformVec3("theSun.diffuse", Point3D(0.5f)); // darken diffuse light a bit
		shinedUponShaderProgram.setUniformVec3("theSun.specular", Point3D(0.9f));

		shinedUponShaderProgram.setUniformVec3("theSun.direction", glm::vec3(0.0f, -1.0f, 0.0f));
		shinedUponShaderProgram.setUniformVec3("theSun.color", glm::vec3(1.0f, 1.0f, 1.0f));

		for (int i = 0; i < 3; i++) {
			shinedUponShaderProgram.use();
			shinedUponShaderProgram.setUniformVec3("ulichniLampi[" + std::to_string(i) + "].position", ulichniLampi[i].position);
			shinedUponShaderProgram.setUniformVec3("ulichniLampi[" + std::to_string(i) + "].color", ulichniLampi[i].color);
			shinedUponShaderProgram.setUniformVec3("ulichniLampi[" + std::to_string(i) + "].ambient", ulichniLampi[i].ambient);
			shinedUponShaderProgram.setUniformVec3("ulichniLampi[" + std::to_string(i) + "].diffuse", ulichniLampi[i].diffuse);
			shinedUponShaderProgram.setUniformVec3("ulichniLampi[" + std::to_string(i) + "].specular", ulichniLampi[i].specular);
			shinedUponShaderProgram.setUniformF("ulichniLampi[" + std::to_string(i) + "].constant", ulichniLampi[i].constant);
			shinedUponShaderProgram.setUniformF("ulichniLampi[" + std::to_string(i) + "].linear", ulichniLampi[i].linear);
			shinedUponShaderProgram.setUniformF("ulichniLampi[" + std::to_string(i) + "].quadratic", ulichniLampi[i].quadratic);

			lightSourceShaderProgram.use();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, ulichniLampi[i].position);
			model = glm::scale(model, glm::vec3(0.2));
			

			lightSourceShaderProgram.setUniformMat4("model", model);
			lightSourceShaderProgram.setUniformVec3("lightColor", ulichniLampi[i].color);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		

		
		//TODO: Optimise includes - only include what is needed.
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