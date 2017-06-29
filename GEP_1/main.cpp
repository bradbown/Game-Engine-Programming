#include "Application.h"

#include <SDL.h>
#include <GL/glew.h>
	    
#include <iostream>

int main(int argc, char* argv[])
{
	engine::Application app(800, 600);

	app.init();
	
	app.run();

	//_CrtDumpMemoryLeaks();

	return true;
}

