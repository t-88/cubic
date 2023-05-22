#include "pch.h"
#include <stdio.h>
#include <stdlib.h>


#include "cube.h"
#include "cubic.h"
#include "shader.h"
#include "shared.h"


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




	Shader shader = Shader("shader/default.shader");
	// Cube cube = Cube();
	Cubic cube = Cubic(2);

	//projection matrix (prespective projection)
	glm::mat4 proj = glm::perspective(glm::radians(45.f),WIDTH / HEIGHT,1.f,100.f);
	//model matrix used for the model transformation (scale , rotate, transform)
	glm::mat4 model = glm::mat4(1.f);
	//view matrix used to controle the view of scene
	glm::mat4 view = glm::mat4(1.f);


	int modelLoc = glGetUniformLocation(shader.id,"model");
	int projLoc = glGetUniformLocation(shader.id,"view");
	int viewLoc = glGetUniformLocation(shader.id,"proj");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void) (io);
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window,true);
	ImGui_ImplOpenGL3_Init("#version 330");



	glEnable(GL_DEPTH_TEST);
	bool isDone = false;
	while(!glfwWindowShouldClose(window) && !isDone) {
		if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) 
			glfwSetWindowShouldClose(window,true);


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glClearColor(0.f,0.f,0.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.activate();


		glUniformMatrix4fv(modelLoc,1,GL_FALSE,&model[0][0]);
		glUniformMatrix4fv(projLoc,1,GL_FALSE,&proj[0][0]);
		glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);




		cube.render(shader);
		cube.input(window);


		ImGui::Begin("Sup first time using imgui");
			ImGui::Checkbox("exit",&isDone);

			ImGui::Checkbox("R",&selectR);
			ImGui::Checkbox("L",&selectL);
			ImGui::Checkbox("U",&selectU);
			ImGui::SliderFloat("rotateR",&rotateR,0,360);
			ImGui::SliderFloat("rotateL",&rotateL,0,360);
			ImGui::SliderFloat("rotateU",&rotateU,0,360);




			ImGui::SliderFloat("rotateX",&rotate_angleX,0,360);
			ImGui::SliderFloat("rotateY",&rotate_angleY,0,360);
			ImGui::SliderFloat("cube x",&cube_x,-10,10);
			ImGui::SliderFloat("cube y",&cube_y,-10,10);
			ImGui::SliderFloat("cube z",&cube_z,-10,10);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cube.clean();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
} 	