
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "src/Shader.h"
#include "src/ShaderProgram.h"
#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"

#define WIDTH 700
#define HEIGHT 500



void Error(int error, const char* details)
{
	printf("ERROR: %d, %s\n", error, details);
}

void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_W:
		printf("Pressed key W. \n");
		glClearColor(0.8f, 0.2f, 0.3f, 1.0f);
		break;
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, 1);
		break;
		
	default:
		break;
	}
}



int main()
{


	if (glfwInit() != GLFW_TRUE)
	{
		printf("Fail to init glfw.");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(Error);


	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW window", nullptr, nullptr);

	if (!window)
	{
		printf("Fail to init window.");
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
	glfwSetKeyCallback(window, OnKeyDown);


	int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!version)
	{
		printf("Failed to load OpenGL. Error: %d \n", version);
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
		-0.3f, 0.5f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.3f, 0.5f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		// first triangle

		-0.3f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.3f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 1.0f,
		//second

		-0.1f, -0.3f,
		0.32f, 0.13f, 0.0f, 1.0f,

		0.1f, 0.0f,
		0.32f, 0.13f, 0.0f, 1.0f,

		-0.1f, 0.0f,
		0.32f, 0.13f, 0.0f, 1.0f,

		0.1f, -0.3f,
		0.32f, 0.13f, 0.0f, 1.0f,
		//second

	};

	GLuint indices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		6, 9, 7

	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer vb(positions, sizeof(positions));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const void *) (sizeof(float) * 2));

	
	IndexBuffer ib(indices, 6);
	

	Shader vertShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
	vertShader.Compile();

	Shader fragShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	fragShader.Compile();

	ShaderProgram program;
	program.AttachShader(&vertShader);
	program.AttachShader(&fragShader);
	program.LinkProgram();

	

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	auto uniformId = glGetUniformLocation(program.GetID(), "u_Color");


	float r = 0.05f;

	float incr = 0.05f;
	
	while (!glfwWindowShouldClose(window))
	{
		program.UseProgram();
		glUniform4f(uniformId, r, 0.0f, 1.0f, 1.0f);
		glBindVertexArray(VAO);

		if (r < 0.0f)
			incr = 0.05f;
		else if (r > 1.0f)
			incr = -0.05f;

		r += incr;

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
