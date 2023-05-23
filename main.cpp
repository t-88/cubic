#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>	


#include "cube.h"
#include "cubic.h"
#include "shader.h"
#include "shared.h"
#include "rectangle.h"



static Rectangle rect;






void init_imGUI(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window,true);
	ImGui_ImplOpenGL3_Init("#version 330");
}
void render_imGUI(Cubic* cube) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("window");
		if(ImGui::Button("random")) {
			printf("asasd\n");
			cube->activate_random_shuffel_mode();
		}

		ImGui::SliderFloat("x",&rect.x,-100.f,100.f);
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
void clean_imGUI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}


int main(){
	srand(time(NULL));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	


	GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"Cubic",NULL,NULL);
    glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, 800, 600);


	Cubic cube = Cubic(2); 

	init_imGUI(window);

	Shader shader = Shader("shader/default.shader");
	Shader shader2D = Shader("shader/2d.shader");

	glm::mat4 proj = glm::perspective(glm::radians(45.f),WIDTH / HEIGHT,1.f,100.f);
	glm::mat4 view = glm::mat4(1.f);

	int projLoc = glGetUniformLocation(shader.id,"proj");
	int viewLoc = glGetUniformLocation(shader.id,"view");

	glm::mat4 orth = glm::ortho(0.0f, WIDTH, HEIGHT, 0.0f,  -1.f , 1.f );
	int orthLoc = glGetUniformLocation(shader2D.id,"orth");



	rect = Rectangle(WIDTH - 100,0,100,100);



	shader.activate(); 
	glEnable(GL_DEPTH_TEST);
	while(!glfwWindowShouldClose(window)) {
		if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) 
			glfwSetWindowShouldClose(window,true);


		glClearColor(0.f,0.f,0.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.activate(); 
		glUniformMatrix4fv(projLoc,1,GL_FALSE,&proj[0][0]);
		glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);
		cube.render(shader,window);
		render_imGUI(&cube);

		shader2D.activate(); 
		glUniformMatrix4fv(orthLoc,1,GL_FALSE,&orth	[0][0]);
		rect.render(shader2D);





		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	cube.clean();
	rect.clean();

	clean_imGUI();
	glfwTerminate();

	return 0;
} 	