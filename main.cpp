#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

unsigned int registerShader(unsigned int type, const char* shaderSource) {
	unsigned int vertexShader;
	vertexShader = glCreateShader(type);

	glShaderSource(vertexShader, 1, &shaderSource, NULL);
	glCompileShader(vertexShader);

	return vertexShader;
}

const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"out vec4 packageForDeliveryToTheFragmentShader;"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos, 1.0);\n"
	"	packageForDeliveryToTheFragmentShader = vec4(aPos.x, 0.0, 0.0, 1.0);\n"
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 myColor;"
"void main()\n"
"{\n"
"FragColor = myColor;\n"
"}\n";

const char* fragmentYellowShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 myColor;"
	"void main()\n"
	"{\n"
	"FragColor = myColor;\n"
	"}\n";

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Valeri Learns OpenGL", NULL, NULL);
	
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	unsigned int vertexShaderId = registerShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShaderId = registerShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	unsigned int yellowFragmentShaderId = registerShader(GL_FRAGMENT_SHADER, fragmentYellowShaderSource);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderId);
	glAttachShader(shaderProgram, fragmentShaderId);
	glLinkProgram(shaderProgram);


	unsigned int yellowShaderProgram = glCreateProgram();
	glAttachShader(yellowShaderProgram, vertexShaderId);
	glAttachShader(yellowShaderProgram, yellowFragmentShaderId);
	glLinkProgram(yellowShaderProgram);

	float triangle1[] = {
		-0.9f, -1.0f, 0.0f,  // left 
		-0.0f, -1.0f, 0.0f,  // right
		-0.45f, 0.0f, 0.0f,  // top 
	};

	float triangle2[] = {
		0.0f, -1.0f, 0.0f,  // left
		0.9f, -1.0f, 0.0f,  // right
		0.45f, 0.0f, 0.0f   // top 
	};

	float triangle3[] = {
		-0.45f, 0.0f, 0.0f,
		0.45f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	unsigned int VBOs[3], VAOs[3];
	glGenBuffers(3, VBOs);
	glGenVertexArrays(3, VAOs);

	// triangle 1 setup
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// triangle 2 setup
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// triangle 3 setup
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle3), triangle3, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
		
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		float time = glfwGetTime();
		float green = sin(time);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
		glUniform4f(vertexColorLocation, 0.0, green, 0.0, 1.0);

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}