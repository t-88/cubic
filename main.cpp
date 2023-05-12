#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include "cube.h"
#include "shader.h"



const float WIDTH  = 800.f;
const float HEIGHT = 600.f;


int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"gl-windoW",NULL,NULL);
    glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, 800, 600);




	Shader shader = Shader("shader/white.shader");
	Cube cube = Cube();

	//projection matrix (prespective projection)
	glm::mat4 proj = glm::perspective(glm::radians(45.f),WIDTH / HEIGHT,1.f , 100.f);
	//model matrix used for the model transformation (scale , rotate, transform)
	glm::mat4 model = glm::mat4(1.f);

	//view matrix used to controle the view of scene
	glm::mat4 view = glm::mat4(1.f);
	int modelLoc = glGetUniformLocation(shader.id,"model");
	int projLoc = glGetUniformLocation(shader.id,"view");
	int viewLoc = glGetUniformLocation(shader.id,"proj");





	glEnable(GL_DEPTH_TEST);
	while(!glfwWindowShouldClose(window)) {
		if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) 
			glfwSetWindowShouldClose(window,true);




		glClearColor(0.f,0.f,0.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.activate();

		model = glm::mat4(1.f);
		model = glm::translate(model,glm::vec3(0.f,0.f,-4.f));
		model = glm::rotate(model,(float)glfwGetTime() * glm::radians(50.f), glm::vec3(0.f,1.f,0.f));


		glUniformMatrix4fv(modelLoc,1,GL_FALSE,&model[0][0]);
		glUniformMatrix4fv(projLoc,1,GL_FALSE,&proj[0][0]);
		glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);

		cube.render();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cube.clean();
	glfwTerminate();
	return 0;
} 	