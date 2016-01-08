// 
// Name: Simpson, Keaton
// Project: 3
// Due: 6/5/2014
// Course: cs-445-01-sp14 
// 
// Description: 
//		Displays a shape with left click toggle rotation
//		and  an interactive right-click menu and keyboard controls to alter the values
//		of each of the units that comprise the location of the 'camera.'
//
#include <stdlib.h>
#ifdef _WIN32 
#include <GL/glut.h> 
#elif __APPLE__ // double underscores 
#include <GLUT/glut.h> 
#endif 

#define _USE_MATH_DEFINES 
#include <math.h> // y0 defined somewhere in math, so I used yO
#include <stdio.h>

const double TWO_PI = 6.2831853;

GLsizei winWidth = 500, winHeight = 500;
GLfloat x0 = 5.0, yO = 5.0, z0 = 5.0; // Viewing-coordinate origin.
GLfloat xref = 0.0, yref = 0.0, zref = 0.0; // Look-at point

GLdouble scale = 1.0;
unsigned int toggle = 0;
GLfloat color[3] = { 1.0, 0.0, 0.0 };
int solid = 0, poly = 1;

GLuint regHex;
GLfloat rotTheta = 3.0;

static void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void displayFcn(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x0, yO, z0, 0, 0, 0, 0, 1, 0);
	glColor3f(color[0], color[1], color[2]);

	if (toggle)
		glRotatef(rotTheta += 3, 0.0, 1.0, 0.0);
	glScalef(scale, scale, scale);

	if (solid) {
		switch (poly) {
		case 1:
			glutSolidCube(1.0);
			break;
		case 2:
			glutSolidDodecahedron();
			break;
		case 3:
			glutSolidTetrahedron();
			break;
		case 4:
			glutSolidOctahedron();
			break;
		case 5:
			glutSolidIcosahedron();
			break;
		case 6:
			glutSolidIcosahedron();
			break;
		}
	}
	else {
		switch (poly) {
		case 1:
			glutWireCube(1.0);
			break;
		case 2:
			glutWireDodecahedron();
			break;
		case 3:
			glutWireTetrahedron();
			break;
		case 4:
			glutWireOctahedron();
			break;
		case 5:
			glutWireIcosahedron();
			break;
		case 6:
			glutWireIcosahedron();
			break;
		}
	}
	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void mouseFcn(GLint button, GLint action, GLint x, GLint y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (action == GLUT_DOWN)
				toggle = !toggle;
			break;
	}
	if (toggle)
		glutIdleFunc(displayFcn);
	else
		glutIdleFunc(NULL);
}

void keyboardFcn(unsigned char key, int x, int y) {
	switch (key) {
	case 'z':
		z0 += -0.05;
		break;
	case 'x':
		x0 += -0.05;
		break;
	case 'y':
		yO += -0.05;
		break;
	case 'Z':
		z0 += 0.05;
		break;
	case 'X':
		x0 += 0.05;
		break;
	case 'Y':
		yO += 0.05;
		break;
	case 's':
		scale -= 0.05;
		break;
	case 'S':
		scale += 0.05;
		break;
	case 'q':
		exit(0);
		break;
	default:
		break;
	}
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(x0, yO, z0, xref, yref, zref, 0.0, 1.0, 0.0);
	glutPostRedisplay();
}

void menu(int opt) { 
	if (opt < 6) {
		poly = opt;
	}
	if (opt > 5 && opt < 10) {
		color[0] = 0.0;
		color[1] = 0.0;
		color[2] = 0.0;
	}

	switch (opt) {
	case 6:
		color[0] = 1.0;
		break;
	case 7:
		color[1] = 1.0;
		break;
	case 8:
		color[2] = 1.0;
		break;
	case 9:
		color[0] = 0.0;
		color[1] = 0.0;
		color[2] = 0.0;
		break;
	case 10:
		solid = 0;
		break;
	case 11:
		solid = 1;
		break;
	}

	glutPostRedisplay();
}

void popupMenu(void) {
	int menuId, sub1, sub2, sub3;

	sub1 = glutCreateMenu(menu);
		glutAddMenuEntry("Cube", 1);
		glutAddMenuEntry("Dodecahedron", 2);
		glutAddMenuEntry("Tetrahedron", 3);
		glutAddMenuEntry("Octahedron", 4);
		glutAddMenuEntry("Icosahedron", 5);

	sub2 = glutCreateMenu(menu);
		glutAddMenuEntry("Red", 6);
		glutAddMenuEntry("Green", 7);
		glutAddMenuEntry("Blue", 8);
		glutAddMenuEntry("Black", 9);

	sub3 = glutCreateMenu(menu);
		glutAddMenuEntry("Wire Frame", 10);
		glutAddMenuEntry("Solid", 11);

	menuId = glutCreateMenu(menu);
		glutAddSubMenu("Shape", sub1);
		glutAddSubMenu("Color", sub2);
		glutAddSubMenu("Solid/Wire", sub3);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Keaton Simpson - Project 3");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouseFcn);
	glutKeyboardFunc(keyboardFcn);
	popupMenu();

	glutMainLoop();
}
