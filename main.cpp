/*
 * =====================================================================================
 *
 *       Filename:  line.h
 *
 *    Description:  Line header
 *
 *        Version:  1.0
 *        Created:  18/04/2019 13:04:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <algorithm> // std::sort
#include <vector> // std::vector
#include <math.h>
#include <time.h>
#include "line.h"
#include "node.h"


#define XMAX_WINDOW 640
#define YMAX_WINDOW 480

int paint = 0;

// color to fill the polygon
int RED = 255;
int GREEN = 0;
int BLUE = 0;

// a structure to hold a mouse click
struct Click {

	/// the position of the mouse click
	int position[2];

	/// constructor
	Click(int x,int y) {

		// set position
		position[0] = x;
		position[1] = y;

		// set next pointer to NULL
		next = 0;
	}

	/// pointer to the next click
	Click* next;
};

/// the top of the stack
Click* top=0;

//------------------------------------------------------------	Push()
//
/// pushes a new data element onto the stack
void Push(int x,int y) {

	// create a new click structure to hold our data
	Click* p = new Click(x,y);

	// set the current top of the stack to be the next
	// of our new element.
	p->next = top;

	// set the top to the new element
	top = p;
}

//------------------------------------------------------------	Pop()
//
/// removes the top element from the stack
void Pop() {

	// ignore an empty stack
	if(!top)
		return;

	// store temp reference to the element on the top
	Click* p = top;

	// get the top to reference the item underneath it
	top = top->next;

	// delete the item
	delete p;
}

/*------------------------------------------------------------	OnReshape()
//
// This function is called when the window gets resized. It
// allows us to set up the camera projection for the scene.
*/
void OnReshape(int w, int h) {
	// set the drawable region of the window to the maximum
	// available window size
	glViewport(0,0,w,h);

	// set up the projection matrix
	glMatrixMode(GL_PROJECTION);

	// clear any previous transform and set to the identity matrix
	glLoadIdentity();

	// just use an orthographic projection
	glOrtho(0, XMAX_WINDOW, YMAX_WINDOW, 0, -1, 1);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
}

void restartColors() {
    RED = 255;
    GREEN = 0;
    BLUE = 0;
}
//------------------------------------------------------------	OnMouseClick()
void OnMouseClick(int button,int state,int x,int y) {

	// if button pressed
	if(state == GLUT_DOWN) {

		// add the mouse x and y coord into the queue
		if (button == GLUT_LEFT_BUTTON)
			Push(x,y);

		// Pop an element
		if (button == GLUT_RIGHT_BUTTON)
            if(paint) {
                paint--;
                while(top) Pop();
            }
            else paint++;
	}
	glutPostRedisplay();
}

/*------------------------------------------------------------	DrawClicks()
//
//	This function is used to draw all data stored in the queue
*/
void DrawClicks() {

	glColor3f(0.5,0.5,1);

	// draw a line between all stored points
	glBegin(GL_LINE_STRIP);
	Click* curr = top;

	// while not at end of the queue
	while (curr) {
		glVertex2iv(curr->position);
		curr = curr->next;
	}
	glEnd();

	glColor3f(1,0.5,0);

	// draw all stored points
	curr = top;
	glBegin(GL_POINTS);
	while (curr) {
		glVertex2iv(curr->position);
		curr = curr->next;
	}
	glEnd();
}

void drawBorders(LINE **lines, int lines_qtd) {
	
    glBegin(GL_LINE_LOOP);

		glColor3f(1,1,1);
        glVertex2i(lines[0]->xA, lines[0]->yA);
		for(int i = 0; i < lines_qtd-1; i++) {
            glVertex2i(lines[i]->xB, lines[i]->yB);
        }

	glEnd();
}

void initializeET(NODE **et, LINE **lines, int lines_qtd) {
    // criando node
    for(int i = 0; i < lines_qtd; i++) {
        
        LINE line = orderLine(lines[i]);
        NODE *node = (NODE *) malloc(sizeof(NODE)); 
        
        initializeNode(node, line);

        int ymin = min(line.yA, line.yB);
        if(et[ymin] == NULL) et[ymin] = node;
        else {
            NODE *aux = et[ymin];
            if(aux->xmin > node->xmin) {
                node->next = aux;
                et[ymin] = node;
            } else {
                while(aux->next != NULL && node->xmin > aux->next->xmin) aux = aux->next;
                node->next = aux->next;
                aux->next = node;
            }
        }
    }
}

void printET(NODE **et) {
    for(int i = 0; i < YMAX_WINDOW; i++) {
        NODE *aux = et[i];
        if(aux != NULL) printf("\nLINHA %d\n\n", i);
        while(aux != NULL) {
            printNode(aux);
            aux = aux->next;
        } 
    }
}

void createET(NODE ***et) {
    
    (*et) = (NODE **) malloc(YMAX_WINDOW * sizeof(NODE *));
    for(int i = 0; i < YMAX_WINDOW; i++) {
        (*et)[i] = NULL;
    }
}

void destroyET(NODE ***et) {
    for(int i = 0; i < YMAX_WINDOW; i++) {
        if((*et)[i] != NULL) {

            NODE *aux1;
            NODE *aux2 = (*et)[i]->next;

            while(aux2 != NULL) {
                aux1 = aux2;
                aux2 = aux1->next;

                free(aux1);
                aux1 = NULL;
            }
            free((*et)[i]);
        }

    }
    free(*et);
    *et = NULL;
}

bool compareX(NODE a, NODE b) {
    return a.xmin < b.xmin;
}

void printAET(std::vector<NODE> aet) {
    for(int i = 0; i < aet.size(); i++) {
        printNode(&(aet[i]));
    }    
}

void updateAET(std::vector<NODE> *aet, NODE **et, int varredura) {
    if(!(*aet).empty()) {
        for(int i = 0; i < (*aet).size(); i++) {
            (*aet)[i].xmin += (*aet)[i].coeficiente;
        }
    }
    
    NODE *aux = et[varredura];
    while(aux != NULL) {
        NODE node = *aux;
        node.next = NULL;

        (*aet).push_back(node);
        aux = aux->next;
    }

    if(!(*aet).empty()) {
        for(int i = (*aet).size()-1; i >= 0; i--) {
            if((*aet)[i].ymax == varredura) {
                (*aet).erase((*aet).begin()+i);
            
            }
        }
    }
    
    std::sort((*aet).begin(), (*aet).end(), compareX);
}

void polygonFiller(LINE **lines, int lines_qtd) {
    NODE **et;

    createET(&et);
    initializeET(et, lines, lines_qtd);
    
    std::vector<NODE> aet;
    for(int y = 0; y < YMAX_WINDOW; y++) {
        updateAET(&aet, et, y);
        if(!aet.empty()) {
           for(int j = 0; j < aet.size(); j++) {
               int begin = (int) ceil(aet[j].xmin);
               int end = (int) floor(aet[j+1].xmin);
               glBegin(GL_POINTS);
               
                   for(int x = begin; x < end; x++) {

                       glColor3ub(RED, GREEN, BLUE);
                       glVertex2i(x, y);

                   }
              
               glEnd();
               j++;
           }
        }
    }

    destroyET(&et);
}

void drawPolygon(LINE **lines, int lines_qtd) {

    drawBorders(lines, lines_qtd);

    polygonFiller(lines, lines_qtd);

}

void fromPointsToLines(LINE **lines, int lines_qtd) {
    if(lines_qtd == 0) return;

    Click *p = top;

    int antx = p->position[0];
    int anty = p->position[1];
    p = p->next; 
    for(int i = 0; i < lines_qtd-1; i++) {
        lineMaker(lines[i], antx, anty, p->position[0], p->position[1]); 
        antx = p->position[0];
        anty = p->position[1];
        p = p->next;
    }

    lineMaker(lines[lines_qtd-1], antx, anty,
                            top->position[0], top->position[1]);
}

int queue_size() {
	
	if(!top)
		return 0;

	Click* p = top;
    int size = 0;
    while(p) {
        p = p->next;
        size++;
    }

	return size;
}

/*------------------------------------------------------------	OnDraw()
//
// glut will call this function whenever the window needs to be
// redrawn.
*/
void OnDraw() {

	// clear the screen & depth buffer
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	// clear the previous transform
	glLoadIdentity();


    if(paint == 0) {
        DrawClicks();
    } else {
        LINE** lines;
        int lines_qtd = queue_size();
        //alocar memoria
        createLines(&lines, lines_qtd);
        
        //transforma os vertices em linhas do polígono
        fromPointsToLines(lines, lines_qtd);
        
        //Desenhar polígono
        drawPolygon(lines, lines_qtd);
        
        //desalocar memoria
        destroyLines(&lines, lines_qtd);
    }


    // currently we've been drawing to the back buffer, we need
	// to swap the back buffer with the front one to make the image visible
	glutSwapBuffers();
}

void keyboard(unsigned char key, int posX, int posY ) {
	switch( key ) {
	case 'e' : case 'E' :
        // erase
        if(paint) paint--;
        else Pop();

        break;
	case 'c' : case 'C' :
        // clear
	    if(paint) paint--;
        while(top) Pop();
        restartColors();

        break;
    case 'r' : case 'R' :
        // recolor
        RED = rand() % 256;
        GREEN = rand() % 256;
        BLUE = rand() % 256;

        break;
    case 'w' : case 'W' :
        //Color polygon
        if(!paint) paint++;

        break;
	default:
		break;
	}
			
	glutPostRedisplay();
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
    //esvazia fila de vertices
    while(top) {
        Pop();
    }
}

//------------------------------------------------------------	main()
//
int main(int argc,char** argv) {

    srand(time(NULL));
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
	
	// set the idle callback
	glutMouseFunc(OnMouseClick);
	
    glutKeyboardFunc(keyboard);
    
     // run our custom initialisation
	OnInit();

	// set the function to be called when we exit
	atexit(OnExit);

	// this function runs a while loop to keep the program running.
	glutMainLoop();
	return 0;
}
