#include "igl/opengl/glfw/renderer.h"
#include "tutorial/sandBox/inputManager.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	Display* disp = new Display(1000, 800, "Wellcome");
	Renderer renderer;
	igl::opengl::glfw::Viewer viewer;
	std::ifstream file("configuration.txt");
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			viewer.load_mesh_from_file(line);
		}
		file.close();
	}
	else {
		std::cout << " config wasn't open " << std::endl;
	}
	
	
	//viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/sphere.obj");
	//viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/cube.obj");
	//viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/bunny.off");
	Init(*disp);
	renderer.init(&viewer);
	disp->SetRenderer(&renderer);
	disp->launch_rendering(true);

	delete disp;
}