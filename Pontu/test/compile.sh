#!/bin/sh
gcc -g testButton.c ../src/engine/Button.c -I ../include $(sdl2-config --cflags --libs) 
#-g pour sortir les option de debbugage
