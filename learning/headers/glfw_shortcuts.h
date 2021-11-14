#ifndef GLFW_SHORTCUTS
#define GLFW_SHORTCUTS

#include "useful_headers.h"

void initializeGLFW();

int initializeGlad();

int checkWindowInitialized(GLFWwindow* window);

void setWindowSize(int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight);

#endif
