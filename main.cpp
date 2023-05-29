#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>	


#include "cube.h"
#include "cubic.h"
#include "shader.h"
#include "shared.h"
#include "rectangle.h"


#include "basic_solver.h"



static BasicSolver bSolver;
static Cubic cube;





void init_imGUI(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window,true);
	ImGui_ImplOpenGL3_Init("#version 330");
}
void render_imGUI() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("window");
		if(ImGui::Button("random!")) {
			cube.activate_random_shuffel_mode();
		}
		if(ImGui::Button("solve!")) {
			std::vector<Operation> ops = bSolver.ooga_booga_solve(cube);
			cube.activate_doing_ops(ops);
			printf("solotion:\n");
			printf("-------------------------------------------------\n");
			for(auto op: ops)
				printf("%s ",opsAsString[op].c_str());
			printf("\n-------------------------------------------------\n");
		}
		ImGui::SliderFloat("solve speed",&rotSpeed,0.5,5);




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



	init_imGUI(window);

	Shader shader = Shader("shader/default.shader");
	Shader shader2D = Shader("shader/2d.shader");

	glm::mat4 proj = glm::perspective(glm::radians(45.f),WIDTH / HEIGHT,1.f,100.f);
	glm::mat4 view = glm::mat4(1.f);

	int projLoc = glGetUniformLocation(shader.id,"proj");
	int viewLoc = glGetUniformLocation(shader.id,"view");

	glm::mat4 orth = glm::ortho(0.0f, WIDTH, HEIGHT, 0.0f,  -1.f , 1.f );
	int orthLoc = glGetUniformLocation(shader2D.id,"orth");



	cube.init();

	shader2D.activate(); 
	glUniformMatrix4fv(orthLoc,1,GL_FALSE,&orth	[0][0]);
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
		cube.render2D(shader2D,window);
		render_imGUI();

		shader2D.activate(); 

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	cube.clean();

	clean_imGUI();
	glfwTerminate();

	return 0;
} 	