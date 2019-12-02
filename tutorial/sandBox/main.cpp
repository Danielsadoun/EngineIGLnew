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
	/*string STRING;
	ifstream infile;
	 infile.open("C:\Dev\EngineIGLnew\tutorial\sandBox\configuration.txt");
	 bool b = infile.is_open();
	 while (getline(infile, STRING).good()) // To get you all the lines.
	{
		//getline(infile, STRING); // Saves the line in STRING.
		//STRING.substr(STRING.length()-2);
		viewer.load_mesh_from_file(STRING);

	}
	infile.close();
	system("pause");
	*/
	//viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/sphere.obj");
	viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/cube.obj");
	viewer.load_mesh_from_file("C:/Dev/EngineIGLnew/tutorial/data/bunny.off");
	Init(*disp);
	renderer.init(&viewer);
	disp->SetRenderer(&renderer);
	disp->launch_rendering(true);

	delete disp;
}