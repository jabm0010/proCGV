#ifndef __CGVSCENE3D
#define __CGVSCENE3D

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


class cgvScene3D {
	protected:
////// Section B: add here the attributes to control the degrees of freedom of the model

		float player1;
		float player2;


////// Section D: add here the attribute/s to control the selected object and to color it yellow


		// Additional attributes		



		bool axes;

	public:
		// Default constructor and destructor
		cgvScene3D();
		~cgvScene3D();

		// Static methods

		// Methods
		// method with the OpenGL calls to render the scene
    void render();


	void drawPlayer1();
	void drawPlayer2();
	
	////// Section B: include here the methods to modify the degrees of freedom of the model

	void movePlayer1(float value);
	void movePlayer2(float value);

	////// Section D: include here the method/s to indicate the selected object

		bool get_axes() {return axes;};
		void set_axes(bool _axes){axes = _axes;};
};

#endif
