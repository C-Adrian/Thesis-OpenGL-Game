#include "useful_headers.h"
#include "glfw_shortcuts.h"
#include "input_processing.h"

int windowWidth = 800;
int windowHeight = 600;

// keep rendering
void keepRendering(GLFWwindow* window) {

	// keep glfw window open as long as glfw hasn't been instructed to close
	while (!glfwWindowShouldClose(window)) {
		
		processInputs(window);

		// rendering
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// check events and swap buffers
		glfwSwapBuffers(window); // drawing on a single buffer might cause visual artifacts. render on a back buffer and swap to the front buffer to avoid this
		glfwPollEvents(); // checks if any events are triggered
	}
}

int main()
{
	initializeGLFW();


	GLFWwindow* mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Learning OpenGL", NULL, NULL);

	checkWindowInitialized(mainWindow);
	glfwMakeContextCurrent(mainWindow);

	initializeGLAD();

	// tell glfw we should use the framebuffer_size_callback function on the window when size callback event is triggered
	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	keepRendering(mainWindow);

	// clean up resources and exit application after we exit the render loop
	glfwTerminate();



	return 0;
}