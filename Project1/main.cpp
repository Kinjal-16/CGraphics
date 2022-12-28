#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include"Shader.h"
#include"Camera.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"model.h"


const unsigned int width = 2880;
const unsigned int height = 1800;




int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");


	Model ourModel("base.obj");
	Model moon("moon.dae");
	Model snowman("hut.obj");
	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	Shader snowmanS("default.vert", "default.frag");



	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::mat4 base = glm::mat4(1.0f);
	// Variables that help the rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(base));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glm::mat4 snownamM = glm::mat4(1.0f);
	snownamM = glm::translate(snownamM, glm::vec3(-10.0f, -10.0f, -10.0f));
	snownamM = base*snownamM ;
	snowmanS.Activate();
	glUniformMatrix4fv(glGetUniformLocation(snowmanS.ID, "model"), 1, GL_FALSE, glm::value_ptr(snownamM));
	glUniform4f(glGetUniformLocation(snowmanS.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(snowmanS.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.04f, 0.01f, 0.09f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.01f;
			prevTime = crntTime;
		}


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0);

		
		camera.ApplyCamera(shaderProgram, "cameraM");
		glUniform1f(glGetUniformLocation(shaderProgram.ID, "scale"), 2.0f);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "cameraFrag"), camera.Position.x, camera.Position.y, camera.Position.z);
		
		ourModel.Draw(shaderProgram);
		
		lightShader.Activate();
		moon.Draw(lightShader);
		glUniform1f(glGetUniformLocation(lightShader.ID, "scale"), 0.05f);
		snowmanS.Activate();
		glm::mat4 snownamM = glm::mat4(1.0f);
		snownamM = glm::translate(snownamM, glm::vec3(-1.0f, -0.5f, 1.0f));
		snownamM = base * snownamM;
		camera.ApplyCamera(snowmanS, "cameraM");
		glUniform1f(glGetUniformLocation(snowmanS.ID, "scale"),1.0f);
		glUniform3f(glGetUniformLocation(snowmanS.ID, "cameraFrag"), camera.Position.x, camera.Position.y, camera.Position.z);
		glUniformMatrix4fv(glGetUniformLocation(snowmanS.ID, "model"), 1, GL_FALSE, glm::value_ptr(snownamM));
		snowman.Draw(snowmanS);
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}