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

glm::vec3 translate[6], rotation[6];
int animate(int i,int flag)
{
	
	if (i == 0)
	{
		if (translate[i].y < 30 && rotation[i].y<90)
		{
			translate[i].y = translate[i].y + 0.1;

		}
	
		if (translate[i].y >=30 && rotation[i].y<=90)
		{
			rotation[i].y = rotation[i].y + 0.1;
			
		}
		
		if (translate[i].y >= 30 && rotation[i].y > 90 && translate[i].x < 35)
		{
			translate[i].x = translate[i].x + 0.1;

		}
		
		
		if (translate[i].y >= 30 && rotation[i].y > 90 && translate[i].x >=35 && rotation[i].y <= 180)
		{
			rotation[i].y = rotation[i].y + 0.1;
			
		}
		
		if (translate[i].x >= 35 && rotation[i].y > 180 && translate[i].y >= 0)
		{
			translate[i].y = translate[i].y - 0.1;

		}
		
		if (translate[i].x >= 35 && rotation[i].y > 180 && translate[i].y < 0 && rotation[i].y <= 270)
		{
			rotation[i].y = rotation[i].y + 0.1;
			
		}
		
		if (rotation[i].y > 270 && translate[i].y < 0 &&  translate[i].x >=15)
		{
			translate[i].x = translate[i].x - 0.1;

		}
		
		if (rotation[i].y > 270 && translate[i].y < 0 && translate[i].x < 15 && rotation[i].y <= 360)
		{
			rotation[i].y = rotation[i].y + 0.1;
			
		}
		if (rotation[i].y >= 360)
			rotation[i].y = 0.0f;
		
	}
	if (i == 1)
	{
		if (translate[i].y < 26 && rotation[i].y < 90)
		{
			translate[i].y = translate[i].y + 0.1;

		}

		if (translate[i].y >= 26 && rotation[i].y <= 90)
		{
			rotation[i].y = rotation[i].y + 0.1;

		}

		if (translate[i].y >= 26 && rotation[i].y > 90 && translate[i].x < 40)
		{
			translate[i].x = translate[i].x + 0.1;

		}


		if (translate[i].y >= 26 && rotation[i].y > 90 && translate[i].x >= 40 && rotation[i].y <= 180)
		{
			rotation[i].y = rotation[i].y + 0.1;

		}

		if (translate[i].x >= 40 && rotation[i].y > 180 && translate[i].y >= 5)
		{
			translate[i].y = translate[i].y - 0.1;

		}

		if (translate[i].x >= 40 && rotation[i].y > 180 && translate[i].y < 5 && rotation[i].y <= 270)
		{
			rotation[i].y = rotation[i].y + 0.1;

		}

		if (rotation[i].y > 270 && translate[i].y < 5 && translate[i].x >=10)
		{
			translate[i].x = translate[i].x - 0.1;

		}

		if (rotation[i].y > 270 && translate[i].y < 5 && translate[i].x < 10 && rotation[i].y <= 360)
		{
			rotation[i].y = rotation[i].y + 0.1;

		}
		if (rotation[i].y >= 360)
			rotation[i].y = 0.0f;

	}
	return flag;
}

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
	GLFWwindow* window = glfwCreateWindow(width, height, "Winter Wonderland", NULL, NULL);
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




	

	Model base("base.obj");
	Model moon("moon.dae");
	Model hut("hut.obj");
	
	Model snowMan[] = { Model("snowman.dae"),Model("snowman.dae"),Model("snowman.dae"),Model("snowman.dae"),Model("snowman.dae"),Model("snowman.dae") };
	// Shader for the base
	Shader baseShader("default.vert", "default.frag");
	// Shader for moon
	Shader lightShader("light.vert", "light.frag");
	// Shader for hut
	Shader hutS("default.vert", "default.frag");
	// Shader for the first snowman
	
	Shader snowManShader[] = { Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag") };





	glm::mat4 baseModel = glm::mat4(1.0f);
	// Variables that help the rotation of the pyramid
	//float rotation = 0.0f;
	double prevTime = glfwGetTime();
	
	
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	// Creates camera object
	Camera camera(width, height, glm::vec3(5.0f, 5.0f, 2.0f));

	// Main while loop
	
	
	translate[0].x = 15.0f, translate[0].z = 0.0f, translate[0].y = 0.0f;
	translate[1].x = 20.0f, translate[0].z = 0.0f, translate[0].y = 0.0f;
	int flag = 0;
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.04f, 0.01f, 0.09f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
			// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 200.0);
		
		lightShader.Activate();
		
		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3 lightPos = glm::vec3(-100.0f, 100.0f, -50.0f);
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		glUniform1f(glGetUniformLocation(lightShader.ID, "scale"), 3.0f);
		camera.ApplyCamera(lightShader, "cameraM");
		moon.Draw(lightShader);

		


	
	
		baseShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(baseShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(baseModel));
		glUniform4f(glGetUniformLocation(baseShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(baseShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		camera.ApplyCamera(baseShader, "cameraM");
		glUniform1f(glGetUniformLocation(baseShader.ID, "scale"), 2.0f);
		glUniform3f(glGetUniformLocation(baseShader.ID, "cameraFrag"), camera.Position.x, camera.Position.y, camera.Position.z);

		base.Draw(baseShader);

		hutS.Activate();
		glm::mat4 hutM = glm::mat4(1.0f);

		hutM = glm::translate(hutM, glm::vec3(-1.0f, -0.5f, 1.0f));
		hutM = baseModel * hutM;
		camera.ApplyCamera(hutS, "cameraM");
		glUniformMatrix4fv(glGetUniformLocation(hutS.ID, "model"), 1, GL_FALSE, glm::value_ptr(hutM));
		glUniform4f(glGetUniformLocation(hutS.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(hutS.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(hutS.ID, "scale"),1.5f);
		glUniform3f(glGetUniformLocation(hutS.ID, "cameraFrag"), camera.Position.x, camera.Position.y, camera.Position.z);
		
		hut.Draw(hutS);
		glm::mat4 snowMan1M = glm::mat4(1.0f);
		
		
		for (int i = 0; i < 3; i++)
		{
			if (i <=1)
			{
				snowManShader[i].Activate();
				glm::mat4 snowMan1M = glm::mat4(1.0f);
				flag=animate(i,flag);
				snowMan1M = glm::translate(snowMan1M, glm::vec3(translate[i].x, translate[i].z, translate[i].y));
				snowMan1M = glm::rotate(snowMan1M, glm::radians(rotation[i].y), glm::vec3(0.0f, 1.0f, 0.0f));
				snowMan1M = baseModel * snowMan1M;
				camera.ApplyCamera(snowManShader[i], "cameraM");
				glUniformMatrix4fv(glGetUniformLocation(snowManShader[i].ID, "model"), 1, GL_FALSE, glm::value_ptr(snowMan1M));
				glUniform4f(glGetUniformLocation(snowManShader[i].ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
				glUniform3f(glGetUniformLocation(snowManShader[i].ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
				glUniform1f(glGetUniformLocation(snowManShader[i].ID, "scale"), 1.0f);
				glUniform3f(glGetUniformLocation(snowManShader[i].ID, "cameraFrag"), camera.Position.x, camera.Position.y, camera.Position.z);
				snowMan[i].Draw(snowManShader[i]);
				//y1 = y1 + 4.0;
			}
			else
				break;
		}
		//y1 = y1 - 12;
		//y1 = 0.0f;
		//for (int i = 3; i < 6; i++)
		//{
		//	y1 = y1 - 4.0;
		//	snowManShader[i].Activate();
		//	glm::mat4 snowMan1M = glm::mat4(1.0f);
		//	snowMan1M = glm::translate(snowMan1M, glm::vec3(x1, z1, y1));
		//	snowMan1M = baseModel * snowMan1M;
		//	camera.ApplyCamera(snowManShader[i], "cameraM");
		//	glUniformMatrix4fv(glGetUniformLocation(snowManShader[i].ID, "model"), 1, GL_FALSE, glm::value_ptr(snowMan1M));
		//	glUniform4f(glGetUniformLocation(snowManShader[i].ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		//	glUniform3f(glGetUniformLocation(snowManShader[i].ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		//	glUniform1f(glGetUniformLocation(snowManShader[i].ID, "scale"), 1.0f);
		//	glUniform3f(glGetUniformLocation(snowManShader[i].ID, "cameraFrag"), camera.Position.x, camera.Position.y, camera.Position.z);
		//	snowMan[i].Draw(snowManShader[i]);
		//	
		//}
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	
	baseShader.Delete();
	lightShader.Delete();
	hutS.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}