#include <cstdlib>
#include <stdio.h>

#include "cgvScene3D.h"

// Constructor methods -----------------------------------

GLfloat colour1[] = { 0,0.7,0 };
GLfloat blue[] = { 0,0,1 };
GLfloat red[] = { 1,0,0 };



cgvScene3D::cgvScene3D () {
	axes = true;
// Section B: initialize the attributes to control the degrees of freedom of the model


	player1 = 0;
	player2 = 0;

// Section D: initialize the attribute/s that identifies the select object and to colour it yellow

}

cgvScene3D::~cgvScene3D() {}


// Public methods ----------------------------------------

void draw_axes(void) {
  GLfloat red[]={1,0,0,1.0};
  GLfloat green[]={0,1,0,1.0};
  GLfloat blue[]={0,0,1,1.0};

	glBegin(GL_LINES);
    glMaterialfv(GL_FRONT,GL_EMISSION,red);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,green);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,blue);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();
}

void cgvScene3D::drawPlayer1(){

	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, red);
		glTranslatef(0, 0, player1);
		glTranslatef(4.5, 0, 0);
		glScalef(0.25, 0.25, 2);
		glutSolidCube(1);
	glPopMatrix();

}


void cgvScene3D::drawPlayer2() {
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, blue);
		glTranslatef(0, 0, player2);
		glTranslatef(-4.5, 0, 0);
		glScalef(0.25, 0.25, 2);
		glutSolidCube(1);
	glPopMatrix();
}




void cgvScene3D::render(void) {

	// lights
	GLfloat light0[4]={5.0,5.0,5.0,1}; // point light source  
	glLightfv(GL_LIGHT0,GL_POSITION,light0); // this light is placed here and it remains still 
	glEnable(GL_LIGHT0);
  
  
	// create the model
	glPushMatrix(); // store the model matrices

	  // draw the axes
	  if (axes) draw_axes();

 		//glLightfv(GL_LIGHT0,GL_POSITION,light0); // the light is placed here and it moves with the scene
	  float mesh_color[4] = {1.0, 0.0, 0.0, 1.0}; 
	  glMaterialfv(GL_FRONT,GL_EMISSION,mesh_color);

///// Section B: include here the visualization of the tree of the model by using the OpenGL stack of matrices 
/////             it is advisable to create an auxiliary method to encapsulate the code to visualize the model
/////             leaving here only the call to this method. In Section D add the names to the mobile parts of the object by 
/////		          the stack of names and control the selected object to colour it yellow




	  //Borde superior
	  glPushMatrix();
	    glMaterialfv(GL_FRONT, GL_EMISSION, colour1);
		glTranslatef(0, 0, 5);
		glScalef(20, 0.5, 0.5);
		glutSolidCube(1);
      glPopMatrix();

	  //Borde inferior
	  glPushMatrix();
	      glMaterialfv(GL_FRONT, GL_EMISSION, colour1);
		  glTranslatef(0, 0, -5);
		  glScalef(20, 0.5, 0.5);
		  glutSolidCube(1);
	  glPopMatrix();

	  drawPlayer1();
	  drawPlayer2();
	
	glPopMatrix (); // restore the modelview matrix 
  
}


void cgvScene3D::movePlayer1(float value) {

	player1 += value;



}


void cgvScene3D::movePlayer2(float value) {
	
	player2 += value;





}


