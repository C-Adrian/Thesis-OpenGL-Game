#ifndef GL_SHORTCUTS_H
#define GL_SHORTCUTS_H

#include "useful_headers.h"

void initializeGLFW();

int checkWindowInitialized(GLFWwindow* window);

int initializeGLAD();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif