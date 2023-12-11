
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "src/Shader.h"
#include "src/ShaderProgram.h"

#define WIDTH 700
#define HEIGHT 500


struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
};


class GLObject
{
public:
	GLObject()
	{
		glGenBuffers(1, &m_buffer);
	}

	~GLObject()
	{
		//glDeleteBuffers(1, &m_buffer);
	}

	void SetData(const Vertex *data, size_t count)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), data, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)sizeof(glm::vec3));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	void Draw()
	{
		//glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
		glDrawArrays(GL_TRIANGLES, 0, 4);
	}

private:
	GLuint m_buffer;
};

GLObject* test = nullptr;

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
		
	case GLFW_KEY_D:
	{



		Vertex v[] = {
			Vertex {
				glm::vec3{ -0.2f, -0.2f, 0.0f },
				glm::vec4 { 0.988f, 0.549f, 0.012f, 1.0f }
			},

			Vertex{
				glm::vec3 { 0.5f, -0.5f, 0.0f },
				glm::vec4 { 0.988f, 0.549f, 0.012f, 1.0f }
			},

			Vertex{
				glm::vec3 { 0.0f,  0.5f, 0.0f },
				glm::vec4 { 252, 140, 3, 1.0f }
			},
		};

		test->SetData(v, 3);
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

	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	glfwSetErrorCallback(Error);


	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW window", nullptr, nullptr);

	if (!window)
	{
		printf("Fail to init window.");
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, OnKeyDown);


	int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!version)
	{
		printf("Failed to load OpenGL. Error: %d \n", version);
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);

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

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const void *) (sizeof(float) * 2));

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	Shader vertShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
	vertShader.Compile();

	Shader fragShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	fragShader.Compile();

	ShaderProgram program;
	program.AttachShader(&vertShader);
	program.AttachShader(&fragShader);
	program.LinkProgram();
	program.UseProgram();
	

	
	while (!glfwWindowShouldClose(window))
	{
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
