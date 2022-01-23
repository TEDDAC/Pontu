#!/bin/sh
gcc -g testButton.c ../src/engine/Button.c ../src/engine/TextureLoader.c -I ../include $(sdl2-config --cflags --libs)
#-g pour sortir les option de debbugage
