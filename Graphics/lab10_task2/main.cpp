#include<Windows.h>    
// first include Windows.h header file which is required    
#include<stdio.h>    
#include<gl/GL.h>   // GL.h header file    
#include<gl/GLU.h> // GLU.h header file    
#include<gl/glut.h>  // glut.h header file from freeglut\include\GL folder    
#include<conio.h>    
#include<stdio.h>    
#include<math.h>    
#include<string.h>   
#include<stdlib.h>

int num = 0;
int width = 0, height = 0;
double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;
float* heights = new float[20];

// Init_OpenGL() function    
void Init_OpenGL()
{
	// set background color to Black    
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
}

// Display_Objects() function    
void Display_Objects(void)
{
	// clearing the window or remove all drawn objects    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (num == 0)
	{
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65.0, width / height, 1.0, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(-0.3, 0.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	else
	{
		glViewport(0, 0, width, height); 
		glMatrixMode(GL_PROJECTION); 
		glLoadIdentity(); 
		glOrtho(-2, 2, -2, 2, -2, 2); 
		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity();
	}


	
		glRotatef(rotate_x, 1, 0, 0);
		glRotatef(rotate_y, 0, 1, 0);
		glRotatef(rotate_z, 0, 0, 1);

	/*glPushMatrix(), which copies the current matrix and adds
	the copy to the top of the stack, and
	glPopMatrix(), which discards the top matrix on the stack*/	    
	for (int r = 0; r < 2; r++)
	{
		for (int j = 0; j < 10; j++)
		{
			float height = heights[(r+1) * j];
			for (int i = 0; i < 3; i++)
			{
				glPushMatrix();
				glTranslatef(-2.0f + float(j) / 2.0f, 0.1 + float(i) * height, 1.0 + ( -2.0 * r));
				glRotatef(90, -1.0f, 0.0f, 0.0f);

				glColor3f(0, 1, 0);

				glScalef(1, 1, 1);
				glutSolidCone(0.2, height, 100, 100);
				glPopMatrix();
			}

			glPushMatrix();
			glTranslatef(-2.0f + float(j) / 2.0f, -0.2, 1.0 + -2.0 * r);
			glRotatef(90, -1.0f, 0.0f, 0.0f);
			glColor3f(0.36, 0.18, 0.03);
			glScalef(1, 1, 1);
			GLUquadricObj* quadratic;
			quadratic = gluNewQuadric();
			gluCylinder(quadratic, 0.05f, 0.05f, 0.3, 32, 32);
			glPopMatrix();
		}
	}

	glFlush();
	glutSwapBuffers();
}
// Reshape() function    
void Reshape(int w, int h)
{
	width = w; height = h;
	//adjusts the pixel rectangle for drawing to be the entire new window    
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//matrix specifies the projection transformation    
	glMatrixMode(GL_PROJECTION);
	// load the identity of matrix by clearing it.    
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	//matrix specifies the modelview transformation    
	glMatrixMode(GL_MODELVIEW);
	// again  load the identity of matrix    
	glLoadIdentity();
	// gluLookAt() this function is used to specify the eye.    
	// it is used to specify the coordinates to view objects from a specific position    
	gluLookAt(-0.3, 0.5, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: rotate_x += 5; break;
	case GLUT_KEY_DOWN: rotate_x -= 5; break;
	case GLUT_KEY_RIGHT: rotate_y += 5; break;
	case GLUT_KEY_LEFT: rotate_y -= 5; break;
	case GLUT_KEY_PAGE_UP: rotate_z += 5; break;
	case GLUT_KEY_PAGE_DOWN: rotate_z -= 5; break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		num = (num+1)%2;
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	
}
// main function    
int main(int argc, char** argv)
{
	for (int i = 0;i <20;i++)
		heights[i] = float(rand() % 30 + 20) / 100.0f;
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("OpenGL Demo");
	Init_OpenGL();
	glutDisplayFunc(Display_Objects);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}