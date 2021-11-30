#include "useful_headers.h"
#include "gl_shortcuts.h"
#include "input_processing.h"
#include "shader.h"

int windowWidth = 800;
int windowHeight = 600;

int main()
{
	initializeGLFW();

	GLFWwindow* mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Learning OpenGL", NULL, NULL);

	checkWindowInitialized(mainWindow);
	glfwMakeContextCurrent(mainWindow);

	initializeGLAD();

	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	float verticesTriangle[] = {
		// Positions		 // Colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};

	Shader shader("shaders/test_shader.vs", "shaders/test_shader.fs");

	unsigned int VAOs[1];
	unsigned int VBOs[1];

	glGenVertexArrays(1, VAOs);
	glGenBuffers(1, VBOs);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	while (!glfwWindowShouldClose(mainWindow)) {

		// Input processing
		processInputs(mainWindow);


		// Rendering

		// Clear the color buffer
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Initialize shader
		shader.use();

		float timeValue = glfwGetTime() * 6;
		float offsetValueX = sin(timeValue) / 4.0f;
		float offsetValueY = cos(timeValue) / 4.0f;
		shader.setFloat("offsetX", offsetValueX);
		shader.setFloat("offsetY", offsetValueY);

		// Draw
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		// Check events and swap buffers
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, VAOs);
	glDeleteBuffers(1, VBOs);


	glfwTerminate();


	return 0;
}
