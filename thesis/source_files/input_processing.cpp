#include "useful_headers.h"
#include "input_processing.h"

bool keyPressed(GLFWwindow* window, int key) {

	return (glfwGetKey(window, key) == GLFW_PRESS);
}

void processInputs(GLFWwindow* window) {

    if (keyPressed(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
        
}
