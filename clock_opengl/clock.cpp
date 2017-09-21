#include <GL/glut.h>
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#define M_PI 3.14159265358979323846
static GLfloat spin = 360.0; // angle of minute pointer
static GLfloat hour_spin = 270.0; // angle of hour pointer

/*
Draw a Circle
arg: R is radius, n is a default value
*/
void DrawCircle(int R, int n=100) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R*cos(2 * M_PI / n*i), R*sin(2 * M_PI / n*i));
	}
	glEnd();
	glFlush();
}

/*
Draw the outlook of a real clock
*/
void Draw_Clock() {
	DrawCircle(45);
	for (int i = 1; i <= 60; i++) {
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		if (i % 15 == 0) {
			glLineWidth(2);//�����߶ο��
			glVertex2f(35 * cos(M_PI / 30 * i), 35 * sin(M_PI / 30 * i)); //�������귶Χ
		}
		else if(i%5 == 0 && i%15 != 0){
			glLineWidth(1.5);//�����߶ο��
			glVertex2f(39 * cos(M_PI / 30 * i), 39 * sin(M_PI / 30 * i)); //�������귶Χ
		}
		else {
			glLineWidth(1.5);//�����߶ο��
			glVertex2f(42 * cos(M_PI / 30 * i), 42 * sin(M_PI / 30 * i)); //�������귶Χ
		}
		glVertex2f(45 * cos(M_PI / 30 * i), 45 * sin(M_PI / 30 * i));
		glEnd();
	}
}

/*
Animation Function
*/
void display() {
	// clear all pixel
	glClear(GL_COLOR_BUFFER_BIT);
	Draw_Clock();
	glPushMatrix();
	Sleep(50);
	glRotatef(spin, 0.0, 0.0, 1.0);
	//void glRotatef(GLfloat angle,  GLfloat x,  GLfloat y,  GLfloat z);
	glColor3f(1.0, 1.0, 1.0);
	glRectf(0.0, -0.3, 30.0, 0.3);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(hour_spin, 0.0, 0.0, 1.0);
	//void glRotatef(GLfloat angle,  GLfloat x,  GLfloat y,  GLfloat z);
	glColor3f(1.0, 1.0, 1.0);
	glRectf(0.0, -0.5, 20.0, 0.5);
	glPopMatrix();

	glutSwapBuffers();

}
/*
Initialization
*/
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);//������ɫģʽ��SMOOTH���ݲ�ֵ, FLAT�и��������
}
/*
mimic the movement of clock pointers
*/
void spinDisplay() {
	spin = spin - 6.0;
	if (spin <= 0.0) 
		spin = 360;
	if (spin == 90.0)
		hour_spin -= 6.0;
	if (hour_spin <= 0.0)
		hour_spin = 360;
	glutPostRedisplay(); //�ػ�ͼ��
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	// ����һ������ƽ�е����壬�������Ͻ�Զ
	glMatrixMode(GL_MODELVIEW); //���߼����������������ʲô��\
	�����ʲô����glMatrixMode�ġ�()�����ѡ��(����)��3��ģʽ: GL_PROJECTION ͶӰ,\
	 GL_MODELVIEW ģ����ͼ, GL_TEXTURE ����.
	glLoadIdentity(); //�ָ����꣬ԭ�����±����Ļ����
}
/*
start the movement by click the left key of mouse
*/
void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(250, 250);	// set window size
	glutInitWindowPosition(100, 100); // set window positon
	glutCreateWindow("hello");	// create a window named "hello"
	init();	// initialize
	glutDisplayFunc(display);	// register animation function as callback function
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);	// interaction with users
	glutMainLoop();
	return 0;

}