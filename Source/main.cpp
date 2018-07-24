#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include "Resources/Headers/stb_image.h"

#include<iostream>
#include<cmath>

#include "Resources/Headers/Shader_new.h"

void processInput (GLFWwindow *);
void framebuffer_size_callback (GLFWwindow *window, int width, int height);

const int WIDTH = 800, HEIGHT = 600;

int flag;
float gamma1 = 0.2f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Shaders", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to open a Window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD\n";
		return -1;
	}

	float vertices[] = {
		//points			  //color             //Texture Co-ordinates
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,0.0f,      //bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f,1.0f,      //top left
		0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 1.0f,   1.0f,1.0f,      //top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 1.0f,   1.0f,0.0f       //bottom right
	};

	float verticesCube[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0,1,2,
		0,2,3
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Shader ourShader("../Source/Resources/Shaders/vertex.glsl", "../Source/Resources/Shaders/frag.glsl");

	// Buffer Gen
	unsigned int VBO, VAO;// EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Texture Gen
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);

	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char *data = stbi_load("Resources/Textures/emoji.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	//Texture 2
	glGenTextures(1, &texture2);

	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char *data1 = stbi_load("Resources/Textures/pepe_high.jpg", &width, &height, &nrChannels, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);

	ourShader.use();
	ourShader.setInt("ourTexture1", 0);
	ourShader.setInt("ourTexture2", 1);

	//int i = 0;

	while (!glfwWindowShouldClose(window))
	{

		glEnable(GL_DEPTH_TEST);

		processInput(window);
		glClearColor(0.5f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue)/2.0f)+0.5f;
		float redValue = (sin(timeValue+20) / 2.0f) + 0.3f;
		float blueValue = (sin(timeValue+10) / 2.0f) + 0.6f;
		int colorLocation = glGetUniformLocation(ourShader.ID, "gColor");
		glUniform4f(colorLocation, redValue, greenValue, blueValue, 1.0f);

		int hPosition = glGetUniformLocation(ourShader.ID, "hPos");
		glUniform3f(hPosition, 0.25f, 0.0f, 0.0f);

		if (i < 2000)
		{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
		else if (i>=2000 && i < 4000)
		{
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		}

		if (i == 4000)
		{
		i = -1;
		}

		i++;

		if (flag == 1)
		{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else if (flag == 2)
		{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 1, 3);
		} */

		//glm::mat4 trans;
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		//trans = glm::scale(trans, glm::vec3(gamma1, gamma1, gamma1));

		//int transLoc;
		//transLoc = glGetUniformLocation(ourShader.ID, "transformPos");
		//glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

		gamma1 = sin(glfwGetTime()) / 2.0f + 0.5f;

		int gammaLocation = glGetUniformLocation(ourShader.ID, "gamma");
		glUniform1f(gammaLocation, gamma1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.use();

		glm::mat4 view;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		int viewLoc;
		viewLoc = glGetUniformLocation(ourShader.ID, "viewMat");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		int projectionLoc;
		projectionLoc = glGetUniformLocation(ourShader.ID, "projectionMat");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i+1);
			model = glm::rotate(model, glm::radians(angle*(float)glfwGetTime()), glm::vec3(1.0f, 0.3f, 0.5f));

			int modelLoc;
			modelLoc = glGetUniformLocation(ourShader.ID, "modelMat");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//glm::mat4 trans1;
		//trans1 = glm::translate(trans1, glm::vec3(-0.5f, 0.5f, 0.0f));
		//trans1 = glm::scale(trans1, glm::vec3(gamma1, gamma1, gamma1));

		//transLoc = glGetUniformLocation(ourShader.ID, "transformPos");
		//glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans1));

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//glm::mat4 trans2;
		//trans2 = glm::translate(trans2, glm::vec3(-0.5f, -0.5f, 0.0f));
		//trans2 = glm::rotate(trans2, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		//trans2 = glm::scale(trans2, glm::vec3(gamma1, gamma1, gamma1));

		//transLoc = glGetUniformLocation(ourShader.ID, "transformPos");
		//glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans2));

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		//glm::mat4 trans3;
		//trans3 = glm::translate(trans3, glm::vec3(0.5f, 0.5f, 0.0f));
		//trans3 = glm::rotate(trans3, -(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		//trans3 = glm::scale(trans3, glm::vec3(gamma1, gamma1, gamma1));

		//transLoc = glGetUniformLocation(ourShader.ID, "transformPos");
		//glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans3));

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);


	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		flag = 1;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		flag = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (gamma1<1.0f)
			gamma1 += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (gamma1>0.0f)
			gamma1 -= 0.001f;
	}
}
