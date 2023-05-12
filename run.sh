#!/bash/sh

g++ main.cpp glad.c  -o main  -I./include/  -lX11 -lpthread -lXrandr -lXi -ldl -lglfw -lGL -lm -lGLEW -lGLU 
./main
