#include <cstdlib>
#include <stdio.h>

#include "cgvScene3D.h"

// Constructor methods -----------------------------------

GLfloat colour1[] = { 0,0.7,0 };
GLfloat blue[] = { 0,0,1 };
GLfloat red[] = { 1,0,0 };
GLfloat white[] = { 1, 1, 1 };


cgvScene3D::cgvScene3D () {
	axes = true;
// Section B: initialize the attributes to control the degrees of freedom of the model

	ballDirX = 1;
	ballDirY = 0.0;

	ballY = 0;
	ballX = 0;

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

void cgvScene3D::drawBall() {
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, white);
		glTranslatef(ballX, 0, ballY);
		glutSolidCube(0.25);
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
	  drawBall();

	glPopMatrix (); // restore the modelview matrix 
  
}


void cgvScene3D::movePlayer1(float value) {
	player1 += value;
}


void cgvScene3D::movePlayer2(float value) {	
	player2 += value;

}

void cgvScene3D::ballMovement() {
	ballX += ballDirX * 0.002;
	ballY += ballDirY * 0.002;

	float racket_width = 0.25;
	float racket_height = 1.75;

	// hit by left racket?
	if (ballX < -4.5 + racket_width &&
		ballX > -4.5 &&
		ballY < player2 + racket_height &&
		ballY > player2 - racket_height) {
		// set fly direction depending on where it hit the racket
		// (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
		float t = ((ballY - player2) / (racket_height)) - 0.02;
		ballDirX = fabs(ballDirX); // force it to be positive
		ballDirY = t;
	}

	// hit by right racket?
	if (ballX < 4.5 &&
		ballX > 4.5 - racket_width &&
		ballY < player1 + racket_height &&
		ballY > player1 - racket_height) {
		// set fly direction depending on where it hit the racket
		// (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
		float t = ((ballY - player1) / (racket_height*2)) - 0.02;
		ballDirX = -fabs(ballDirX); // force it to be negative
		ballDirY = t;
	}

	// hit left wall?
	if (ballX < -5) {
//		++score_right;
		ballX = 0;
		ballY = 0;
		ballDirX = fabs(ballDirX); // force it to be positive
		ballDirY = 0;
	}

	 // hit right wall?
	if (ballX > 5) {
//		++score_left;
		ballX = 0;
		ballY = 0;
		ballDirX = -fabs(ballDirX); // force it to be negative
		ballDirY = 0;
	}

	// hit top wall?
	if (ballY > 4.7) {
		ballDirY = -0.5; // force it to be negative
	}

	// hit bottom wall?
	if (ballY < -4.7) {
		ballDirY = 0.5; // force it to be positive
	}

}

