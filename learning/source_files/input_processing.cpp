#include "input_processing.h"

bool keyPressed(int key) {

	return (glfwGetKey(mainWindow, key == GLFW_PRESS));
}

void processInputs() {

	if (keyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(mainWindow, true);
	}

}
