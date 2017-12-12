#include <cstdlib>
#include <stdio.h>

#include "cgvInterface.h"

extern cgvInterface interface; // the callbacks must be static and this object is required to access to the variables of the class                   // ellos a las variables de la clase

// Constructor and destructor methods -----------------------------------

cgvInterface::cgvInterface():camType(CGV_PARALLEL)  {
//// Section D: initialize the attributes to select objects by list of impacts
	mode = CGV_VISUALIZE;
	selected_object = -1;
	pressed_button = false;
}

cgvInterface::~cgvInterface () {}


// Public methods ----------------------------------------
void cgvInterface::create_world(void) {
	//Changed the camera view to the top
	camera = cgvCamera(cgvPoint3D(0,8.0,0),cgvPoint3D(0,0,0),cgvPoint3D(0,0,1),
		                                1*5, 1*5, 0.1, 200);

}

void cgvInterface::configure_environment(int argc, char** argv, 
			                       int _width_window, int _height_window, 
			                       int _pos_X, int _pos_Y, 
													 string _title)
													 {
	// initialization of the interface variables																	
	width_window = _width_window;
	height_window = _height_window;

	// initialization of the display window
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(_width_window,_height_window);
  glutInitWindowPosition(_pos_X,_pos_Y);
	glutCreateWindow(_title.c_str());

	glEnable(GL_DEPTH_TEST); // enable the removal of hidden surfaces by using the z-buffer
	//Modified to put the colour black
  glClearColor(0,0,0,0.0); // define the background color of the window

	glInitNames();

	glEnable(GL_LIGHTING); // enable the lighting of the scene
  glEnable(GL_NORMALIZE); // normalize the normal vectors required by the lighting computation. 

  create_world(); // create the world (scene) to be rendered in the window
}

void cgvInterface::init_rendering_loop() {
	glutMainLoop(); // initialize the visualization loop of OpenGL
}

void cgvInterface::set_glutKeyboardFunc(unsigned char key, int x, int y) {
  switch (key) {

	 case 'w':
		 interface.scene.movePlayer1(0.2);
	 break;
	 case 's':
		 interface.scene.movePlayer1(-0.2);
	break;
	 case 'i':
		 interface.scene.movePlayer2(0.2);
		 break;
	 case 'k':
		 interface.scene.movePlayer2(-0.2);
		 break;

    case 'a': // enable/disable the visualization of the axes
			interface.scene.set_axes(interface.scene.get_axes()?false:true);

	  break;
    case 27: // Escape key to exit
      exit(1);
    break;
  }
	glutPostRedisplay(); // renew the content of the window
}

void cgvInterface::set_glutReshapeFunc(int w, int h) {
  // dimension of the viewport with a new width and a new height of the display window 


  // store the new values of the viewport and the display window. 
  interface.set_width_window(w);
  interface.set_height_window(h);

  // Set up the kind of projection to be used
  interface.camera.apply(interface.camType);

}

void cgvInterface::set_glutDisplayFunc() {
	GLuint impact_list[1024]; // array with the list of impacts when it is rendered in selection mode


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window and the z-buffer

	// set up the viewport
	glViewport(0, 0, interface.get_width_window(), interface.get_height_window());

	// Apply the camera and projection transformations according to its parameters and to the mode (selection or visualization)
	interface.camera.apply(interface.camType);

	// Render the scene
	interface.scene.render();

	glutSwapBuffers(); // it is used instead of glFlush(), to avoid flickering	
}

void cgvInterface::init_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc); 
	glutVisibilityFunc(interface.visible);
}

void cgvInterface::visible(int iVis)
{
	if (iVis == GLUT_VISIBLE)
		glutIdleFunc(interface.idle);
	else
		glutIdleFunc(NULL);

	return;
}

void cgvInterface::idle(void)
{
	float fTime, fSimTime;
	float static fLastIdleTime = 0;

	fTime = 1000 / 60;

	fSimTime = fTime - fLastIdleTime;

	interface.scene.ballMovement();

	fLastIdleTime = fTime;

	glutPostRedisplay();
}