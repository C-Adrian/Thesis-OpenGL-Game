#include "glfw_shortcuts.h"

void initializeGLFW() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set glfw version to 3.*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // set glfw version to *.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set OpelGL profile to core (only uses minimal functionality)
}

int checkWindowInitialized(GLFWwindow* window) {

	if (window == NULL) {

		printf("GLFW window creation failed\n");
		glfwTerminate();
		return -1;
	}

	return 1;
}

int initializeGlad() {

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

		printf("GLAD initialization faied\n");
		return -1;
	}

	return 1;
}

// set the rendering zone for the window
void setWindowSize(int width, int height) {
	glViewport(0, 0, width, height);
}

// callback function for window resize event
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight) {
	setWindowSize(newWidth, newHeight);
}