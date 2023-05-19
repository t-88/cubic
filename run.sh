#!/bash/sh

g++ main.cpp  ./imgui/*.cpp  glad.c  -o main  -I./include/ -I./include/imgui -lX11 -lpthread -lXrandr -lXi -ldl -lglfw -lGL -lm -lGLEW -lGLU

./main
