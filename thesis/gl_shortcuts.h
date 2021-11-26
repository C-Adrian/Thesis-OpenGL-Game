#ifndef GLFW_SHORTCUTS
#define GLFW_SHORTCUTS

#include "useful_headers.h"

void initializeGLFW();

int checkWindowInitialized(GLFWwindow* window);

int initializeGLAD();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void checkShaderCompilation(unsigned int shader);

void checkShaderProgram(unsigned int shaderProgram);

#endif