#include "input_processing.h"

bool keyPressed(GLFWwindow* window, int key) {

	return (glfwGetKey(window, key) == GLFW_PRESS);
}

void processInputs(GLFWwindow* window) {

    if (keyPressed(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }

    if (keyPressed(window, GLFW_KEY_F1)) {

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (keyPressed(window, GLFW_KEY_F2)) {

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
        
}
