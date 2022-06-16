compile: winbootbutton.c
	gcc -Wall -shared -o libwinbootbutton.so -fPIC winbootbutton.c `pkg-config --cflags --libs libxfce4panel-2.0` `pkg-config --cflags --libs gtk+-3.0`
