#ifndef __CGVINTERFACE
#define __CGVINTERFACE

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <string>

#include "cgvScene3D.h"
#include "cgvCamera.h"

using namespace std;

typedef cameraMode interfaceMode; 

class cgvInterface {
	protected:
		// Attributes
		int width_window; // initial width of the display window
		int height_window;  // initial height of the display window

		cgvScene3D scene; // scene to be rendered in the display window defined by cgvInterface. 
		cgvCamera camera; // Camera to visualize the scene
		cameraType camType; // Camera type 	CGV_PARALLEL or CGV_PERSPECTIVE

		///// Section D: attributes to selecting by mouse
		interfaceMode mode; // CGV_VISUALIZE: in the window where the scene is usually rendered  
							// CGV_SELECT: the user has clicked, the scene must be rendered in selection mode to compute the list of 							  // impacts
		int cursorX,cursorY; // pixel of the screen where the mouse is placed while clicking or dragging 
		int selected_object; // code of the selected object, -1 if there is no selected object
		bool pressed_button; // button pressed (true) or released(false)

	public:
		// Default constructor and destructor
		cgvInterface();
		~cgvInterface();

		// Static methods
		// event callbacks
		static void set_glutKeyboardFunc(unsigned char key, int x, int y); // method to control keyboard events
		static void set_glutReshapeFunc(int w, int h); // method to define the camera and the viewport
		                                               // it is automatically called when the window is resized
		static void set_glutDisplayFunc(); // method to render the scene

		static void  set_idleFunc();

		
		// create the world that is render in the window
		void create_world(void);
		// initialize all the parameters to create a display window
		void configure_environment(int argc, char** argv, // main parameters
			                       int _width_window, int _height_window, // width and height of the display window
			                       int _pos_X, int _pos_Y, // init position of the display window
													 string _title // title of the display window
													 ); 
		void init_callbacks(); // initialize all the callbacks

		void init_rendering_loop(); // render the scene and wait for an event in the interface

		static void visible(int vis);
		static void idle();
		void init_idleFunc();

		// methods get_ and set_ to access the attributes
		int get_width_window(){return width_window;};
		int get_height_window(){return height_window;};

		void set_width_window(int _width_window){width_window = _width_window;};
		void set_height_window(int _height_window){height_window = _height_window;};
};

#endif
