#include <stdlib.h>
#include <GL/glut.h>

#define XMAX_WINDOW 640
#define YMAX_WINDOW 480
//------------------------------------------------------------	OnReshape()
//
// This function is called when the window gets resized. It
// allows us to set up the camera projection for the scene.
//
void OnReshape(int w, int h) {
	// set the drawable region of the window to the maximum
	// available window size
	glViewport(0,0,w,h);

	// set up the projection matrix
	glMatrixMode(GL_PROJECTION);

	// clear any previous transform and set to the identity matrix
	glLoadIdentity();

	// just use an orthographic projection
	glOrtho(-12,12,-12,12,-1,1);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
}

//------------------------------------------------------------	OnDraw()
//
// glut will call this function whenever the window needs to be
// redrawn.
//
void OnDraw() {

	// clear the screen & depth buffer
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	// clear the previous transform
	glLoadIdentity();

	//
	// The simplest way to render geometry within openGL is to use
	// whats known as immediate mode. The drawing takes place between
	// glBegin() and glEnd(). glBegin takes the type of geometry you
	// want to draw, these can be on of the following :
	//
	//  	GL_POINTS
	//  	GL_LINES
	//  	GL_LINE_LOOP
	// 		GL_LINE_STRIP
	//  	GL_TRIANGLES
	//  	GL_TRIANGLE_STRIP
	//  	GL_TRIANGLE_FAN
	//  	GL_QUADS
	//  	GL_QUAD_STRIP
	//  	GL_POLYGON
	//
	// You can place as many calls to glVertex3f inbetween glBegin() and
	// glEnd(). For example, 6 calls to glVertex* between glBegin and glEnd
	// would produce 2 triangles....
	//
	glBegin(GL_LINE_LOOP);

		glColor3f(1,0,0);
		glVertex2i(-10,-10);

		glColor3f(0,1,0);
		glVertex2i(10,-10);

		glColor3f(0,0,1);
		glVertex2i(0,10);

	glEnd();

	// currently we've been drawing to the back buffer, we need
	// to swap the back buffer with the front one to make the image visible
	glutSwapBuffers();
}

//------------------------------------------------------------	OnInit()
//
void OnInit() {
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
}

//------------------------------------------------------------	OnExit()
//
void OnExit() {
}

//------------------------------------------------------------	main()
//
int main(int argc,char** argv) {

	// initialise glut
	glutInit(&argc,argv);

	// request a depth buffer, RGBA display mode, and we want double buffering
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);

	// set the initial window size
	glutInitWindowSize(XMAX_WINDOW, YMAX_WINDOW);

	// create the window
	glutCreateWindow("Polygon Filler");

	// set the function to use to draw our scene
	glutDisplayFunc(OnDraw);

	// set the function to handle changes in screen size
	glutReshapeFunc(OnReshape);
	
	// run our custom initialisation
	OnInit();

	// set the function to be called when we exit
	atexit(OnExit);

	// this function runs a while loop to keep the program running.
	glutMainLoop();
	return 0;
}
