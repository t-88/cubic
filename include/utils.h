#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

char* readFile(char* file_path ) {
	FILE* file = fopen(file_path,"rb");	
	if(!file) {
		printf("ERROR: %m\n");
		  return NULL;
	}
	long len;
	//printf("%s\n",file_path);
	if(fseek(file,0,SEEK_END)) {
		printf("ERROR: %m");
		fclose(file);
		  return NULL;
	}
	len = ftell(file);
	char* buffer = (char*) calloc(len,sizeof(char*));

	if(fseek(file,0,SEEK_SET)) {
		printf("ERROR: %m");
		fclose(file);
		return NULL;
	}
	fread(buffer,sizeof(char),len,file);	

	fclose(file);
	return buffer;
}


#endif