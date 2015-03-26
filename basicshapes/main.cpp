/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Basic Shapes" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



#include <iostream>
#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float _angle = 30.0f;
float _camera_angle = 0.0f;

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y) {    //The current mouse coordinates
	switch (key) {
		case 27: //Escape key
			exit(0); //Exit the program
	}
}

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
}

void update(int value){
    _angle += 2.0f;
    if (_angle > 360.0f) {
        _angle -= 360.0f;
    }
    _camera_angle += 0.5f;
    if (_camera_angle > 360.0f){
        _camera_angle -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}

//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
    glRotatef(_angle, 0.1f, -0.1f, 1.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, 0.0f, -5.0f);

    glPushMatrix();
    glTranslatef(0.0f, -1.0, 0.0f);
    glRotatef(_angle, 0.0f, 0.0f, 1.0f);
    
    glColor3f(0.0f, 0.75f, 0.0f);
	glBegin(GL_TRIANGLES); //Begin triangle coordinates
	glVertex3f(-0.7f, -0.5f, 0.0f);
	glVertex3f(0.7f, -0.5f, 0.0f);
	glVertex3f(-0.4f, 0.5f, 0.0f);

    glVertex3f(0.7f, -0.5f, 0.0f);
	glVertex3f(0.4f, 0.5f, 0.0f);
	glVertex3f(-0.4f, 0.5f, 0.0f);
	glEnd();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2.0f);
    glRotatef(_angle, 0.0f, 1.0f, 0.0f);
    glScalef(0.7f, 0.7f, 0.7f);
    
    glColor3f(0.75f, 0.0f, 0.0f);
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
    glVertex3f(-0.4f, -0.5f, 0.0f);
    glVertex3f(+0.6f, -0.5f, 0.0f);
    glVertex3f(+0.4f, +0.5f, 0.0f);
    glVertex3f(-0.6f, +0.5f, 0.0f);

	glEnd(); //End quadrilateral coordinates
	glPopMatrix();
    glPushMatrix();
    glScalef(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 0.7f);
	glBegin(GL_TRIANGLES); //Begin triangle coordinates
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.0f, 1.0f, 0.0f);
    glRotatef(_angle, 1.0f, 2.0f, 3.0f);

    glBegin(GL_TRIANGLES);
	//Triangle
	glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	
	glEnd(); //End triangle coordinates
	glPopMatrix();
    glPopMatrix();
    
	glutSwapBuffers(); //Send the 3D scene to the screen
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400); //Set the window size
	
	//Create the window
	glutCreateWindow("Basic Shapes - videotutorialsrock.com");
	initRendering(); //Initialize rendering
	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutTimerFunc(25, update, 0);
    glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}









