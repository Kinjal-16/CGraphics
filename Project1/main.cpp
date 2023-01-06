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
bool collision[6] = {false};
bool wallCollide[6] = { false };
float collisionRotaion[] = { 120.0f,120.0f,120.0f,120.0f,120.0f,120.0f };
float collisiontranslation[] = { 5.0f,5.0f,5.0f,5.0f,5.0f,5.0f };

float collisionWalltranslation[] = { 5.0f,5.0f,5.0f,5.0f,5.0f,5.0f };



void collisionResolutionSnowman(int i)
{
	if (collisionRotaion[i] > 0)
	{
		rotation[i].y = rotation[i].y + 0.5;
		collisionRotaion[i] = collisionRotaion[i] - 0.5;
	}
	else if (collisiontranslation[i] > 0)
	{
		translate[i].x = translate[i].x + 0.01 * glm::sin(glm::radians(rotation[i].y));
		translate[i].y = translate[i].y + 0.01 * glm::cos(glm::radians(rotation[i].y));
		collisiontranslation[i] = collisiontranslation[i] - 0.01;
	}
	else
	{
		collision[i] = false;
		collisionRotaion[i] = 120.0f;
		collisiontranslation[i] = 5.0f;
	}
}
void collisionDetectionSnowman(int k)
{
	for (int i = 0; i < 6; i++)
	{
		if (k == i)
			continue;
		float x = translate[i].x - translate[k].x;
		float y = translate[i].y - translate[k].y;
		float z = translate[i].z - translate[k].z;
		float dist=glm::sqrt(glm::pow(x,2)+ glm::pow(y, 2)+ glm::pow(z, 2));
		if (dist <= 5)
		{
			
			collision[i] = true;
			collisionResolutionSnowman(k);
		}
	}
	if (translate[k].x > 0 && 45 - translate[k].x <= 5)
	{
		collision[k] = true;
		collisionResolutionSnowman(k);
	}

	

	if (35 - abs(translate[k].y) <= 5)
	{
		std::cout << abs(translate[k].y) << std::endl;

		collision[k] = true;
		collisionResolutionSnowman(k);
	}
	
	
}

void animate(int i)
{
	/*
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

	}*/
	translate[i].x = translate[i].x +0.01 * glm::sin(glm::radians(rotation[i].y));
	translate[i].y = translate[i].y +0.01 * glm::cos(glm::radians(rotation[i].y));
	collisionDetectionSnowman(i);
	
}
float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};
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
	// Shader for the  snowmenn
	
	Shader snowManShader[] = { Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag"),Shader("default.vert", "default.frag") };

	// Sahder for the skybox
	Shader skyboxS("SkyBox.vert","SkyBox.frag");



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
	translate[1].x = 35.0f, translate[0].z = 0.0f, translate[0].y = 0.0f;
	rotation[0].y = 90.0f;
	rotation[1].y = 270.0f;
	int flag = 0;

	// Create VAO, VBO, and EBO for the skybox
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	/*
	
	GL TEXTURE CUBEMAP POSITIVE X -- right 
	GL TEXTURE CUBEMAP NEGATIVE X -- left 
	GL TEXTURE CUBEMAP POSITIVE Y -- top  
	GL TEXTURE CUBEMAP NEGATIVE Y -- bottom 
	GL TEXTURE CUBEMAP POSITIVE Z -- front 
	GL TEXTURE CUBEMAP NEGATIVE Z -- back
	*/
	std::string facesCubemap[6] =
	{
		"px.png", //Right
		"nx.png", //Left
		"py.png", //Top
		"ny.png", //bottom
		"pz.png",//front
		"nz.png" //back
	};

	//Creation of the cubemap texture object
	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGBA,
				width,
				height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
			stbi_image_free(data);
		}
	}
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
		
		
		for (int i = 0; i < 2; i++)
		{
			if (i <=1)
			{
				snowManShader[i].Activate();
				glm::mat4 snowMan1M = glm::mat4(1.0f);
				if (collision[i])
					collisionResolutionSnowman(i);
				else
					animate(i);
				
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
		glDepthFunc(GL_LEQUAL);

		skyboxS.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
		// The last row and column affect the translation of the skybox (which we don't want to affect)
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxS.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxS.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
		// where an object is present (a depth of 1.0f will always fail against any object's depth value)
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Switch back to the normal depth function
		glDepthFunc(GL_LESS);
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