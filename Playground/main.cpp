
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "src/Shader.h"
#include "src/ShaderProgram.h"
#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"
#include "src/Texture.h"
#include "src/VertexArray.h"

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

	case GLFW_KEY_A:
	{
		static bool a = false;
		a = !a;
		auto draw = a ? GL_POLYGON_MODE: GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		printf("AAAA \n");
		break;
	}
		
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

	GLfloat positions[] = {
		-0.3f, 0.5f,
		0.0, 1.0f,

		0.3f, 0.5f,
		0.4f, 1.0f,

		0.0f, 1.0f,
		0.0, 0.0f,
		// first triangle

		-0.3f, 0.0f,
		0.0, 0.5f,

		0.3f, 0.0f,
		0.4f, 0.5f,

		0.0f, 0.5f,
		0.0, 0.0f,
		//second

		-0.1f, -0.3f,
		0.6f, 1.0f,

		0.1f, 0.0f,
		1.0f, 1.0f,

		-0.1f, 0.0f,
		0.6f, 0.0f,

		0.1f, -0.3f,
		1.0f, 0.0f,
		//second

	};


	GLuint indices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		6, 9, 7

	};

	//GLuint VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	VertexArray va;
	VertexBuffer vb(positions, sizeof(positions));


	va.AddAttribute<GLfloat>(2);
	va.AddAttribute<GLfloat>(2);
	va.CreateAttribPointers();

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	//
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(float) * 4, (const void *) (sizeof(float) * 2));
	
	IndexBuffer ib(indices, 12);
	

	Shader vertShader("assets/shaders/vertex.glsl", GL_VERTEX_SHADER);
	vertShader.Compile();

	Shader fragShader("assets/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	fragShader.Compile();

	ShaderProgram program;
	program.AttachShader(&vertShader);
	program.AttachShader(&fragShader);
	program.LinkProgram();
	program.SetUniform1i("u_Texture", 2);

	Texture texture("assets/textures/c_tree.jpg");
	texture.Bind(0);


	
	while (!glfwWindowShouldClose(window))
	{
		program.Bind();
		//glBindVertexArray(VAO);
		
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
