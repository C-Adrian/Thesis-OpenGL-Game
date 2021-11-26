#include "useful_headers.h"
#include "gl_shortcuts.h"
#include "input_processing.h"

int windowWidth = 800;
int windowHeight = 600;


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.2f, 0.2f, 0.8f, 1.0f);\n"
"}\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.8f, 0.8f, 0.2f, 1.0f);\n"
"}\0";



int main()
{
	initializeGLFW();

	GLFWwindow* mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Learning OpenGL", NULL, NULL);

	checkWindowInitialized(mainWindow);
	glfwMakeContextCurrent(mainWindow);

	initializeGLAD();

	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);


	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompilation(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompilation(fragmentShader);

	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	checkShaderCompilation(fragmentShader2);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); 
	checkShaderProgram(shaderProgram);

	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	checkShaderProgram(shaderProgram2);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);
	

	float verticesTriangle[] = {
		-0.75f, -0.5f,  0.0f,
		 0.25f, -0.5f,  0.0f,
		-0.25f,  0.5f,  0.0f,
	};

	float verticesTriangle2[] = {
	   -0.25f, -0.5f,  0.0f,
		0.75f, -0.5f,  0.0f,
		0.25f,  0.5f,  0.0f
	};

	/*
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[]{
		0, 1, 3,
		1, 2, 3
	};
	*/

	unsigned int VAOs[2];
	unsigned int VBOs[2];
	unsigned int EBO;

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle2), verticesTriangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 
	*/

	while (!glfwWindowShouldClose(mainWindow)) {
		
		// Input processing
		processInputs(mainWindow);


		// Rendering
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// check events and swap buffers
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgram2);


	glfwTerminate();

	return 0;
}
