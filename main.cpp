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

#include <iostream>
#include <string>

using namespace std;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lastX = 400, lastY = 300;
glm::vec3 direction;
bool firstMouse = true;
float yaw, pitch;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraDir = glm::normalize(cameraPos - cameraTarget);
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDir));
glm::vec3 cameraUp = glm::cross(cameraDir, cameraRight);

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

float mouseSpeed = 1.0f;
float maxVertical = 90.0f;
float minVertical = -90.0f;
float maxHori = 90.0f;
float minHori = -90.0f;

struct Bullet {
	glm::vec3 pos;
	glm::vec3 dir;
};

vector<Bullet> bullets;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		bullets.push_back({ cameraPos, cameraFront });
	}
}

float fov = 45.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}

int main()
{
	Graphics g;
	g.init();

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	Window window;
	window.init(SCR_WIDTH, SCR_HEIGHT, "Learning Open GL", Color(0.0f, 0.0f, 0.0f, 1.0f));
	window.makeActive();
	window.registerCursorPositionCallback(mouse_callback);
	window.registerMouseButtonCallback(mouse_button_callback);
	window.registerScrollCallback(scroll_callback);
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

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);  
	// render loop
	// -----------
	while (!window.shouldClose())
	{
		// input
		// -----
		processInput(window.getRaw());

		window.clear();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

		// get matrix's uniform location and set matrix
		lightSourceShaderProgram.use();

		lightSourceShaderProgram.setUniformMat4("view", view);
		lightSourceShaderProgram.setUniformMat4("projection", projection);

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
		shinedUponShaderProgram.setUniformMat4("view", view);
		shinedUponShaderProgram.setUniformMat4("projection", projection);
		
		glm::mat4 objectModel = glm::mat4(1.0f);
		objectModel = glm::translate(objectModel, glm::vec3(5.0f, -2.0f, 0.0f));
		
		
		shinedUponShaderProgram.setUniformVec3("objectColor", glm::vec3(0.77f, 0.33f, 0.03f));
		shinedUponShaderProgram.setUniformVec3("lightColor", lightColor);
		shinedUponShaderProgram.setUniformVec3("lightPos", lightPos);
		shinedUponShaderProgram.setUniformVec3("viewerPos", cameraPos);
		objectModel = glm::scale(objectModel, glm::vec3(5.0f));
		shinedUponShaderProgram.setUniformMat4("model", objectModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		window.swapBuffers();
		g.pollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	float cameraSpeed = 0.004;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}