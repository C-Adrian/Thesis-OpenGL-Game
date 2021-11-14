#ifndef GLFW_SHORTCUTS
#define GLFW_SHORTCUTS

void initializeGLFW();

int initializeGlad();

void createMainWindow(int width, int height, const char* name);

int checkWindowInitialized();

void makeContextCurrent();

void setFramebufferSizeCallback(void* callback);

void setWindowSize(int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight);

#endif
