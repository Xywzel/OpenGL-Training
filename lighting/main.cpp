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
float _light_pos = 0.0f;
float _light_move = 0.02f;
bool _lightsOn = true;
bool _smooth = true;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0); //Exit the program
        case 'l': //L key
            if(_lightsOn){
                glDisable(GL_LIGHTING);
                _lightsOn = false;
            } else {
                glEnable(GL_LIGHTING);
                _lightsOn = true;
            }
            break;
        case 's':
            if(_smooth){
                glDisable(GL_SMOOTH);
                _smooth = false;
            } else {
                glEnable(GL_SMOOTH);
                _smooth = true;
            }
            break;
        default:
            break;
	}
}

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
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
    _light_pos += _light_move;
    if (_light_pos > 4.0f || _light_pos < -4.0f) {
        _light_move = - _light_move;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, -9.0f);

    GLfloat posLight[] = {0.6f, 0.0f, 0.0f, 1.0f};
    GLfloat position[] = {2.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, posLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    GLfloat dirLight[] = {0.0f, 0.0f, 0.6f, 1.0f};
    GLfloat dirrection[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, dirLight);
    glLightfv(GL_LIGHT1, GL_POSITION, dirrection);

    GLfloat moveLight[] = {0.0f, 0.9f, 0.0f, 1.0f};
    GLfloat movePos[] = {_light_pos, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, moveLight);
    glLightfv(GL_LIGHT2, GL_POSITION, movePos);

    glRotatef(_angle, 0.1f, 1.0f, 0.0f);
    glPushMatrix();
    glColor3f( 1.0f, 1.0f, 1.0f);
    
    glBegin(GL_QUADS); // Cube
    
    glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glNormal3f( 1.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glNormal3f( 1.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glNormal3f( 1.0f, 0.0f,-1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    glNormal3f( 1.0f, 0.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
	
    glNormal3f(-1.0f, 0.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glNormal3f(-1.0f, 0.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glNormal3f( 1.0f, 0.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);
    glNormal3f( 1.0f, 0.0f,-1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
	
    glNormal3f(-1.0f, 0.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glNormal3f(-1.0f, 0.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
	
    glEnd(); //End triangle coordinates

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

