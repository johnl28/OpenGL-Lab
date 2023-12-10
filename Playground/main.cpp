
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "src/Shader.h"
#include "src/ShaderProgram.h"



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
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(600, 500, "GLFW window", nullptr, nullptr);

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

	glViewport(0, 0, 600, 500);

	const Vertex vertices[] = {
		Vertex { 
			glm::vec3{ -0.5f, -0.5f, 0.0f },
			glm::vec4 { 1.0f, 0.0f, 0.0f, 1.0f }
		},

		Vertex { 
			glm::vec3 { 0.5f, -0.5f, 0.0f },
			glm::vec4 { 0.0f, 1.0f, 0.0f, 1.0f }
		},

		Vertex {
			glm::vec3 { 0.0f,  0.5f, 0.0f },
			glm::vec4 { 0.0f, 0.0f, 1.0f, 0.0f }
		},

		Vertex {
			glm::vec3 { 1.0f,  -0.5f, 0.0f },
			glm::vec4 { 0.0f, 0.0f, 1.0f, 0.0f }
		},

	};

	test = new GLObject();
	test->SetData(vertices, 4);
	


	
	Shader vertex("shaders/vertex.glsl", GL_VERTEX_SHADER);
	vertex.Compile();

	Shader fragment("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	fragment.Compile();

	ShaderProgram shaderProgram;
	shaderProgram.AttachShader(&vertex);
	shaderProgram.AttachShader(&fragment);
	shaderProgram.LinkProgram();
	shaderProgram.UseProgram();


	//auto shaderProgram = glCreateProgram();

	//glAttachShader(shaderProgram, vertex.GetID());
	//glAttachShader(shaderProgram, fragment.GetID());
	//glLinkProgram(shaderProgram);
	//
	//GLint success = 0;
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	char buff[500];
	//	glGetProgramInfoLog(shaderProgram, 500, nullptr, buff);
	//	std::cout << buff << std::endl;
	//}

	//glUseProgram(shaderProgram);


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		test->Draw();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
