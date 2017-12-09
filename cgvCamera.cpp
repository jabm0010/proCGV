#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif


#include <math.h>
#include <stdio.h>

#include "cgvCamera.h"

// Constructors
cgvCamera::cgvCamera(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up,
	double _right, double _top,
	double _znear, double _zfar):zoomFactor(0.01), currentZoom(1)
{
	setCameraParameters(_PV, _rp, _up);
	setParallelParameters(_right, _top, _znear, _zfar);
}


cgvCamera::~cgvCamera () {}

void cgvCamera::setCameraParameters(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up) {
	PV = _PV;
	rp = _rp;
	up = _up;
}

void cgvCamera::getCameraParameters(cgvPoint3D& _PV, cgvPoint3D& _rp, cgvPoint3D& _up) {
	_PV = PV;
	_rp = rp;
	_up = up;
}

void cgvCamera::setParallelParameters(double _right, double _top,
	double _znear, double _zfar)
{
	xwmin = -_right; // left
	xwmax = _right;  
	ywmin = -_top; // bottom
	ywmax = _top;
	znear = _znear;
	zfar = _zfar;

}


void cgvCamera::getParallelParameters(double& _xwmin, double& _xwmax, double& _ywmin, double& _ywmax, 
										double& _znear, double& _zfar)
{
	_xwmin = xwmin;
	_xwmax = xwmax;
	_ywmin = ywmin;
	_ywmax = ywmax;
	_znear = znear;
	_zfar = zfar;
}



void cgvCamera::apply(cameraType type) {

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	if (mode == CGV_SELECT) {
		////// TODO: Section D: get the current size of the viewport
		////// TODO: Section D: Modify the projection using the function gluPickMatrix and 
		//////            generate the view volume around the clicked pixel
	}


	if (type==CGV_PARALLEL) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (type==CGV_PERSPECTIVE) {
		double fovy, aspect; 
		computePerspectiveParameters(fovy, aspect, xwmin, xwmax, ywmin, ywmax);
		gluPerspective(fovy,aspect,znear,zfar);
	}
	
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(PV[X],PV[Y],PV[Z], rp[X],rp[Y],rp[Z], up[X],up[Y],up[Z]);
}

void cgvCamera::setZoomFactor(double factor) {
	zoomFactor = factor; 
}

void cgvCamera::zoomIn() {}
void cgvCamera::zoomOut() {}


void cgvCamera::computePerspectiveParameters(double &fovy, double &aspect, 
	double _xwmin, double _xwmax, double _ywmin, double _ywmax)
{

}


void cgvCamera::setSelection(int _width_selection, int _height_selection,
	int _cursorX, int _cursorY) {
	mode = CGV_SELECT;
	// width and height of the selection window
	width_selection = _width_selection;
	height_selection = _height_selection;
	// pixel position (user click)
	cursorX = _cursorX;
	cursorY = _cursorY;
}

