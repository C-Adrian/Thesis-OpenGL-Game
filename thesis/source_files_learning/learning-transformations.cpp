#include "useful_headers.h"
#include "gl_shortcuts.h"
#include "input_processing.h"
#include "shader.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int windowWidth = 800;
int windowHeight = 600;

int main()
{
	initializeGLFW();

	GLFWwindow* mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Learning OpenGL", NULL, NULL);

	checkWindowInitialized(mainWindow);
	glfwMakeContextCurrent(mainWindow);

	initializeGLAD();

	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	// Set up shader

	Shader shader("shaders/test_shader_texture.vs", "shaders/test_shader_texture.fs");


	// Set up vertex data and buffers

	float texCoordmin = 0.0f;
	float texCoordmax = 1.0f;

	float vertices[] = {
		// Position           // Color            // Texture coordinates
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   texCoordmax, texCoordmax,
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   texCoordmax, texCoordmin,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   texCoordmin, texCoordmin,
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   texCoordmin, texCoordmax
	};
	unsigned int indices[] = {
		0, 1, 3, // First triangle
		1, 2, 3  // Second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	int width, height, nrChannels;

	// First texture
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Never use mipmap as last parameter for magnifying, because mipmaps are only useful for downscaling

	unsigned char* data = stbi_load("textures_learning/container.jpg", &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Texture loading failed\n";
	}

	stbi_image_free(data);

	// Second texture

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("textures_learning/face.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Texture loading failed\n";
	}

	float opacity = 0.2f;




	while (!glfwWindowShouldClose(mainWindow)) {

		// Input processing
		processInputs(mainWindow);

		if (keyPressed(mainWindow, GLFW_KEY_MINUS)) {
			opacity = opacity > 0 ? opacity - 0.001f : opacity;
		}

		if (keyPressed(mainWindow, GLFW_KEY_EQUAL)) {
			opacity = opacity <= 1 ? opacity + 0.001f : opacity;
		}


		// Rendering

		// Clear the color buffer
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Initialize shader
		shader.use();
		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);
		shader.setFloat("opacity", opacity);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 1.0, 0.0f));

		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// Draw
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Draw 2

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.5f));
		trans = glm::scale(trans, 0.2f + glm::vec3(0.3f, 0.3f, 0.3f) * abs(sin((float)glfwGetTime())));


		transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// Check events and swap buffers
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();


	return 0;
}
