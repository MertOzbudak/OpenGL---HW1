
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define  TIMER_PERIOD  50 // Period for the timer.
#define  TIMER_ON     1    // 0:disable timer, 1:enable timer
#define START 0
#define RUN 1
#define END 2
#define D2R 0.0174532

int cox = 0;//for cloud movement COORDİNATE X(cox)
int appState = START;

bool button1 = false;
bool button2 = false;
bool button3 = false;

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;

int  winWidth, winHeight; // current Window width and height

bool checkCircle(float px, float py, float cx, float cy, float R);//mouse movements for buttons

//
// to draw circle, center at (x,y)
//  radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}
void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}
void print(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}
// display text with variables.
void vprint(int x, int y, void *font, char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}
void vprint2(int x, int y, float size, char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}
void startDisplay(){

	// DRAW A RECTANGLE FOR TITLE FUNCTIONS

	glColor3f(1, 1, 1);
	glRectf(-300, 55, 300, -255);

	glColor3f(0, 0, 0);
	vprint2(-150, 0, 0.3, "HOMEWORK #1");
	vprint2(-80, -50, 0.2, "Spring 2016");
	glColor3f(1, 0.2, 0.2);
	vprint2(-100, -120, 0.2, "MERT OZBUDAK");
	vprint2(-68, -180, 0.2, "21301809");

}
void runDisplay(){
	
	//FOR SCENE FUNCTIONS

	// DRAW 1.QUADS FOR AIR
	//glRectf(-300, 55, 300, -255);

	glBegin(GL_QUADS);
	glColor3f(0.3, 0.6, 1);
	glVertex2f(-320, 65);
	glVertex2f(320, 65);
	glColor3f(1, 1, 1);
	glVertex2f(320, -195);
	glVertex2f(-320, -195);
	glEnd();

	// DRAW 2.QUADS FOR GRASS
	glBegin(GL_QUADS);

	glColor3ub(50, 120, 65);
	glVertex2f(-320, -195);
	glVertex2f(320, -195);
	glColor3f(0.3, 1, 0.1);
	glVertex2f(320, -255);
	glVertex2f(-320, -255);
	glEnd();

	//RECTANGLE FOR HOME
	glColor3ub(100, 150, 200);
	glRectf(260, -110, 90, -195);

	//HOME  LİNE
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(260, -110);
	glVertex2f(260, -195);
	glVertex2f(260, -110);
	glVertex2f(90, -110);
	glVertex2f(90, -110);
	glVertex2f(90, -195);
	glEnd();

	//RECTANGLE FOR WINDOW
	glColor3f(1, 1, 1);
	glRectf(196, -128, 245, -157);

	//WINDOW LINE
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(196, -128);
	glVertex2f(245, -128);
	glVertex2f(245, -157);
	glVertex2f(196, -157);
	glVertex2f(196, -128);
	glEnd();

	//FOUR PART WINDOW
	glBegin(GL_LINES);
	glVertex2f(196, -144);
	glVertex2f(245, -144);
	glVertex2f(220, -128);
	glVertex2d(220, -157);

	glEnd();
	
	//DOOR
	glColor3ub(190, 160, 40);
	glRectf(130, -195, 160, -155);

	//DOOR LİNE
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(130, -195);
	glVertex2f(130, -155);
	glVertex2f(160, -155);
	glVertex2f(160, -195);
	glEnd();

	//DOOR KNOP
	glBegin(GL_POINTS);
	glVertex2f(138, -178);
	glEnd();
	
	//TRIANGLE FOR HOME-ROOF
	glBegin(GL_TRIANGLES);
	glColor3ub(170, 80, 90);
	glVertex2f(80, -110);
	glVertex2f(167, -58);
	glVertex2f(265, -110);
	glEnd();

	//ROOF LINE
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(265, -110);
	glVertex2f(80, -110);
	glVertex2f(167, -58);
	glVertex2f(265, -110);
	glEnd();

	//CLOUD
	glColor3f(1, 1, 1);
	circle(-250 + cox, 16, 17);
	circle(-227 + cox, 23, 16);
	circle(-232 + cox, 2, 15);
	circle(-205 + cox, 18, 15);
	circle(-210 + cox, 4, 14);

	//DRAW RECTANGLE TO HIDE CLOUD
	//RIGHT SIDE
	glColor3f(0, 0, 0);
	glRectf(-320, 111, -400, -270);
	//LEFT SIDE
	glColor3f(0, 0, 0);
	glRectf(320, 111, 400, -270);






}
void endDisplay(){

	exit(0);
}
void display()
{


	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//BUTTONS

	//TITLE CIRCLE
	glColor3f(1, 0, 0);
	circle(-200, 200, 80);
	if (button1)
	{
		glColor3f(1, 0, 0);

	}
	else
	{
		glColor3f(1, 0.2, 0);
		circle(-200, 200, 75);
	}

	glColor3f(1, 1, 1);
	vprint2(-255, 190, 0.3, "TITLE");


	//SCENE CIRCLE
	glColor3ub(0, 255, 0);
	circle(10, 200, 80);
	if (button2)
	{
		glColor3ub(0, 255, 0);

	}
	else
	{
		glColor3ub(120, 255, 0);
		circle(10, 200, 75);
	}
	glColor3f(1, 1, 1);
	vprint2(-55, 190, 0.3, "SCENE");

	//EXIT CIRCLE
	glColor3f(0, 0, 1);
	circle(220, 200, 80);
	if (button3)
	{
		glColor3f(0, 0, 1);

	}
	else
	{
		glColor3f(0, 0.3, 1);;
		circle(220, 200, 75);
	}
	glColor3f(1, 1, 1);
	vprint2(180, 190, 0.3, "EXIT");


	switch (appState)
	{
	case START:startDisplay();
		break;
	case RUN:runDisplay();
		break;
	case END:endDisplay();
		break;

	}

	glutSwapBuffers();


}
//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}
void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}
//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;

	}
	// to refresh the window it calls display() function
	glutPostRedisplay();
}
//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;

	}
	// to refresh the window it calls display() function
	glutPostRedisplay();
}
//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{	//all possible functions
		if (appState == START && button1 == true)
			appState = START;
		else if (appState == START && button2 == true)
			appState = RUN;
		else if (appState == START && button3 == true)
			appState = END;
		else if (appState == RUN && button1 == true)
			appState = START;
		else if (appState == RUN && button3 == true)
			appState = END;
	}
	glutPostRedisplay();
}
//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}
bool checkCircle(float px, float py, float cx, float cy, float R) {
	float dx = px - cx;
	float dy = py - cy;
	float d = sqrt(dx*dx + dy*dy);
	return d <= R;
}
void onMove(int x, int y) {

	int lx = x - winWidth / 2;
	int ly = winHeight / 2 - y;

	button1 = checkCircle(lx, ly, -200, 200, 80);
	button2 = checkCircle(lx, ly, 10, 200, 80);
	button3 = checkCircle(lx, ly, 220, 200, 80);





	glutPostRedisplay();
}
#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	if (appState == RUN){

		if (cox < WINDOW_WIDTH - 150)
			cox++;
		else
			cox = -150;

	}
	glutPostRedisplay(); // display()

}
#endif
void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(5.0);


}
void main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("HW#1-Spring 2016");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);
	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}