#ifndef __CGVCAMERA
#define __CGVCAMERA

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


#include "cgvPoint3D.h"

typedef enum {
	CGV_PARALLEL,
	CGV_PERSPECTIVE
} cameraType;

typedef enum {
	CGV_VISUALIZE,
	CGV_SELECT
} cameraMode;


class cgvCamera {

	protected:
		// attributes
		
		// view plane: parameters parallel projection and frustum
		GLdouble xwmin, xwmax, ywmin, ywmax;

		// distances of near and far planes
		GLdouble znear, zfar;

		// point of view
		cgvPoint3D PV;

		// view reference point	
		cgvPoint3D rp;

		// up vector 
		cgvPoint3D up;

		// zoom factor
		double zoomFactor; 
		double currentZoom; 

		////// Section D: attributes required to generate a volume around the selected pixel
		cameraMode mode; // camera used to visualize (CGV_VISUALIZE) or to select (CGV_SELECT)
		int cursorX, cursorY; // selection position of the viewport. The volume is generated from this position
		// to select by list of impacts
		int width_selection, height_selection; // size of the window to select by list of impacts		


		// Methods

	public:
		// Default Constructors and destructor
		cgvCamera() :xwmin(-1), xwmax(1), ywmin(-1), ywmax(1), znear(0.1), zfar(100),
			PV(cgvPoint3D(-1, 0, 0)), rp(cgvPoint3D(0,0,0)), up(cgvPoint3D(0,1,0)), zoomFactor(0.01), currentZoom(1) {}
		cgvCamera(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up,
			double _right, double _top, 
			double _znear, double _zfar);	
		~cgvCamera();


		// Methods
		// Defining the camera parameters
		void setCameraParameters(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up);
		void getCameraParameters(cgvPoint3D& _PV, cgvPoint3D& _rp, cgvPoint3D& _up);

		// Defining the projection
		void setParallelParameters(double _right, double _top,
			double _znear, double _zfar);
		
		void getParallelParameters(double& _xwmin, double& _xwmax, double& _ywmin, double& _ywmax,
			double& _znear, double& _zfar);

		// Apply the camera
		//// Section D: apply the view and projection transformations to the object of the scene according to the camera parameters
		//// If the mode is CGV_VISUALIZE the transformations will be applied as usual, 
		//// If the mode is CGV_SELECT  it is necessary to implement the calculations of the selection by list of impacts
		void apply(cameraType type); // apply the view and projection transformations to the object of the scene. 
		                    
		void setZoomFactor(double factor); // Modify the zoom factor
		void zoomIn(); 
		void zoomOut(); 

		////// Section D: Methods to change the camera mode
		void setSelection(int _width_selection, int _height_selection,
						  int _cursorX, int _cursorY);
		void setVisualization() { mode = CGV_VISUALIZE; };

		cgvCamera &operator=(const cgvCamera &cam) {
			this->xwmin = cam.xwmin; 
			this->xwmax = cam.xwmax; 
			this->ywmin = cam.ywmin;
			this->ywmax = cam.ywmax;

			this->znear = cam.znear; 
			this->zfar = cam.zfar; 

			this->PV = cam.PV;

			this->rp = cam.rp;

			this->up = cam.up; 
			return *this; 
		}

protected:
	void computePerspectiveParameters(double &fovy, double &aspect, 
			double _xwmin, double _xwmax, double _ywmin, double _ywmax);

};

#endif

