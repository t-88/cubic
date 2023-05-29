#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "utils.h"

typedef struct {
	char* vertex;
	char* fragment;

} ShaderSource;



class Shader {
	public: 
		uint32_t id;
		ShaderSource source;




		Shader(const char* path) {
			source = readShaderFromFile((char*) path);

			uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex,1,&source.vertex,NULL);
			glCompileShader(vertex);


			uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment,1,&source.fragment,NULL);
			glCompileShader(fragment);

			if(!check_compile_error(vertex,(char*)"") || !check_compile_error(fragment,(char*)""))
				goto defer;

	   		id = glCreateProgram();
			
			glAttachShader(id,vertex);
			glAttachShader(id,fragment);
			glLinkProgram(id);
		
			glDeleteShader(vertex);
			glDeleteShader(fragment);

		defer:
			free(source.vertex);
			free(source.fragment);
		}
		int check_compile_error(uint32_t id, char* text) {
			int status = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS,&status);
			if(!status) {
				char info[512];
				glGetShaderInfoLog(id,512,NULL,info);

				printf("[ERROR-69] compile shader error, debug: %s info: %s",text,info);
				return 0;
			}
			return 1;
		}
		void activate() {
			glUseProgram(id);	
		}
		void free_mem() {
			glDeleteProgram(id);
		}


        ShaderSource readShaderFromFile(char* file_path) {
            FILE* file = fopen(file_path,"rb");	
            if(!file) {
                printf("ERROR: %m\n");
                exit(0);	
            }
            
            size_t addr;
            char* line = NULL;
            
            
            int readingOrder = 0; // 0 = vertex , 1 = fragment
            int total_len = 0;
            int len;
            
            
            ShaderSource source;
            source.vertex = NULL;
            source.fragment = NULL;

            while((len = getline(&line,&addr,file)) != -1) {
                total_len += len;
                if(strcmp(line,"//::fragment::\n") == 0) readingOrder = 1;
                else if(strcmp(line,"//::vertex::\n") == 0) readingOrder = 0;
                else if(readingOrder == 0) {
                    if(source.vertex == NULL) source.vertex = (char*)calloc(sizeof(char) , total_len);
                    else source.vertex = (char*)realloc(source.vertex,total_len); 
                    strcat(source.vertex,line);
                } else {
                    if(source.fragment == NULL) source.fragment = (char*)calloc(sizeof(char) , total_len);
                    else source.fragment = (char*)realloc(source.fragment,total_len); 

                    strcat(source.fragment,line);
                }
            }

            fclose(file);
            return source;
        }
};




#endif