#include "useful_headers.h"
#include "gl_shortcuts.h"
#include "input_processing.h"

int windowWidth = 800;
int windowHeight = 600;

/*
	OpenGL pipeline: 2 parts
		-part 1: transforms 3d coordinates int 2d coordinates
		-part 2: transforms 2d coordinates int colored pixels

	Pipeline can execute multiple processes simulateneously due to GPUs having many processing core.
	Processing cores run small programs called shaders.
	Shaders are configurable and are written in GLSL.

	Vertex data gets sent to pipeline:
	-> Vertex shader -> Shape assembly -> Geometry Shader -> Tests and Blending -> Fragment Shader -> Rasterization

	Vertex data:
	Vertex attributes, like 3D position and color value.
	OpenGL needs primitives to know how to interpret the data (ex: GL_POINTS, GL_TRIANGLES, GL_LINE_STRIP).

	Clipping is skipping drawing something outside of the view for optimization.
*/


/*
* OpenGL requires having a shader file, we'll be using this one:
*
* #version 330 core
* layout (location = 0) in vec3 aPos;

* void main()
* {
*	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
* }
*/

// Store vertex shader here for now:
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

/*
* OpenGL requires having a fragment shader, we'll be using this one:
*
* #version 330 core
* out vec4 FragColor;
*
* void main()
* {
*	FragColor = vec4(0.2f, 0.2f, 0.8f, 1.0f);
* }
*/

// Store fragment shader here for now:
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.2f, 0.2f, 0.8f, 1.0f);\n"
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

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Attach shader source code
	glCompileShader(vertexShader); 
	checkShaderCompilation(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompilation(fragmentShader);

	// We need a shader program. It's a final version of multiple shaders combined.
	// To use compiled shaders, we need to link them to a shader program object and activate it.
	// Will be used when we do render calls.

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);  // Link the attached shaders.
	checkShaderProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
	};
	/*
	* Normalized device coordinates (NDC) vary from -1 to 0. Every other coordinate is clipped/discarded.
	* NDC coordinates - transform to screen-space coordinates via viewport transform using data provided with glViewport.
	* screen-space-coordinates - transform to fragments -> fragment shader
	*/

	unsigned int VBO; // Vertex Buffer Objects (VBO) - store many vertices in GPU's memory (fast).
	unsigned int VAO; // OpenGL require we use a Vertex Attribute Object (VAO) which we have to bind.

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy user-defined data into currently bound buffer.
	/*
	* GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
	* GL_STATIC_DRAW: the data is set only once and used many times.
	* GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	*/

	// We need to specify how openGL should interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	/*
	* First param - which vertex attribute we want to configure (we specified layout location = 0 in vertexShader).
	* Second param - size of vertex attribute (vec3 has 3).
	* Third param - the type of data (a vec* in GLSL has floating point values).
	* Fourth param - whether we want data to be normalized. Since we already use float values, there is no need. Would be useful to set GL_TRUE if using int/byte.
	* Fifth param - stride (distance between consecutive vertex attributes). 3 Floats in our case. Data is tightly packed (no space until next vertext attribute), so could have used 0 to let openGL determined it.
	* Sixth param - offset where position data begins in the buffer.
	*/
	glEnableVertexAttribArray(0); // Multiple VBOs can be used. Current VBO is bound to GL_ARRAY_BUFFER. Previously defined VBO i still bound, so vertex attribute is 0.

	// Keep main window open
	while (!glfwWindowShouldClose(mainWindow)) {

		processInputs(mainWindow);

		// rendering
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram); // Every shader/rendering call after glUseProgram uses this program object (and the shaders within it).
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check events and swap buffers
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
} 
