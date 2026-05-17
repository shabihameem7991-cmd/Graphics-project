#include<windows.h>
#include <GL/glut.h>
#define PI          3.141516
#include<math.h>


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3ub(59, 60, 61);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 2.0f);
        glVertex2f(9.0f, 2.0f);
        glVertex2f(9.0f, 0.0f);
	glEnd();
    glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(2.0f, 1.0f);
        glVertex2f(2.0f, 0.9f);
        glVertex2f(1.0f, 0.9f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(3.0f, 1.0f);
        glVertex2f(4.0f, 1.0f);
        glVertex2f(4.0f, 0.9f);
        glVertex2f(3.0f, 0.9f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(5.0f, 1.0f);
        glVertex2f(6.0f, 1.0f);
        glVertex2f(6.0f, 0.9f);
        glVertex2f(5.0f, 0.9f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(7.0f, 1.0f);
        glVertex2f(8.0f, 1.0f);
        glVertex2f(8.0f, 0.9f);
        glVertex2f(7.0f, 0.9f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(162, 165, 168);
        glVertex2f(0.0f, 2.0f);
        glVertex2f(0.0f, 2.2f);
        glVertex2f(9.0f, 2.2f);
        glVertex2f(9.0f, 2.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(1.0f, 2.2f);
        glVertex2f(1.1f, 2.2f);
        glVertex2f(1.1f, 2.0f);
        glVertex2f(1.0f, 2.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(2.0f, 2.2f);
        glVertex2f(2.1f, 2.2f);
        glVertex2f(2.1f, 2.0f);
        glVertex2f(2.0f, 2.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(3.0f, 2.2f);
        glVertex2f(3.1f, 2.2f);
        glVertex2f(3.1f, 2.0f);
        glVertex2f(3.0f, 2.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(4.0f, 2.2f);
        glVertex2f(4.1f, 2.2f);
        glVertex2f(4.1f, 2.0f);
        glVertex2f(4.0f, 2.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(5.0f, 2.2f);
        glVertex2f(5.1f, 2.2f);
        glVertex2f(5.1f, 2.0f);
        glVertex2f(5.0f, 2.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(6.0f, 2.2f);
        glVertex2f(6.1f, 2.2f);
        glVertex2f(6.1f, 2.0f);
        glVertex2f(6.0f, 2.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(7.0f, 2.2f);
        glVertex2f(7.1f, 2.2f);
        glVertex2f(7.1f, 2.0f);
        glVertex2f(7.0f, 2.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 251, 252);
        glVertex2f(8.0f, 2.2f);
        glVertex2f(8.1f, 2.2f);
        glVertex2f(8.1f, 2.0f);
        glVertex2f(8.0f, 2.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(20, 181, 33);
        glVertex2f(0.0f, 2.2f);
        glVertex2f(0.0f, 3.0f);
        glVertex2f(9.3f, 3.0f);
        glVertex2f(9.0f, 2.2f);
	glEnd();
    glBegin(GL_QUADS);
        glColor3ub(42, 42, 43);
        glVertex2f(0.0f, 4.5f);
        glVertex2f(9.0f, 4.5f);
        glVertex2f(9.0f, 3.0f);
        glVertex2f(0.0f, 3.0f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(175, 175, 179);
        glVertex2f(0.0f, 4.5f);
        glVertex2f(0.0f, 4.6f);
        glVertex2f(9.0f, 4.6f);
        glVertex2f(9.0f, 4.5f);
	glEnd();
    glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(1.0f, 4.5f);
        glVertex2f(1.0f, 4.6f);
        glVertex2f(1.1f, 4.6f);
        glVertex2f(1.1f, 4.5f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(2.0f, 4.5f);
        glVertex2f(2.0f, 4.6f);
        glVertex2f(2.1f, 4.6f);
        glVertex2f(2.1f, 4.5f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(3.0f, 4.5f);
        glVertex2f(3.0f, 4.6f);
        glVertex2f(3.1f, 4.6f);
        glVertex2f(3.1f, 4.5f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(4.0f, 4.5f);
        glVertex2f(4.0f, 4.6f);
        glVertex2f(4.1f, 4.6f);
        glVertex2f(4.1f, 4.5f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(5.0f, 4.5f);
        glVertex2f(5.0f, 4.6f);
        glVertex2f(5.1f, 4.6f);
        glVertex2f(5.1f, 4.5f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(6.0f, 4.5f);
        glVertex2f(6.0f, 4.6f);
        glVertex2f(6.1f, 4.6f);
        glVertex2f(6.1f, 4.5f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(7.0f, 4.5f);
        glVertex2f(7.0f, 4.6f);
        glVertex2f(7.1f, 4.6f);
        glVertex2f(7.1f, 4.5f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(8.0f, 4.5f);
        glVertex2f(8.0f, 4.6f);
        glVertex2f(8.1f, 4.6f);
        glVertex2f(8.1f, 4.5f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(0.5f, 3.6f);
        glVertex2f(0.5f, 3.7f);
        glVertex2f(1.4f, 3.7f);
        glVertex2f(1.4f, 3.6f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(2.5f, 3.6f);
        glVertex2f(2.5f, 3.7f);
        glVertex2f(3.5f, 3.7f);
        glVertex2f(3.5f, 3.6f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(5.0f, 3.6f);
        glVertex2f(5.0f, 3.7f);
        glVertex2f(6.0f, 3.7f);
        glVertex2f(6.0f, 3.6f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 250, 252);
        glVertex2f(7.0f, 3.6f);
        glVertex2f(7.0f, 3.7f);
        glVertex2f(8.0f, 3.7f);
        glVertex2f(8.0f, 3.6f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(38, 179, 25);
        glVertex2f(0.0f, 4.6f);
        glVertex2f(0.0f, 5.2f);
        glVertex2f(9.0f, 5.2f);
        glVertex2f(9.0f, 4.6f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(40, 148, 250);
        glVertex2f(0.0f, 5.2f);
        glVertex2f(0.0f, 6.5f);
        glVertex2f(9.0f, 6.5f);
        glVertex2f(9.0f, 5.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(247, 177, 96);
        glVertex2f(0.0f, 6.5f);
        glVertex2f(0.0f, 8.0f);
        glVertex2f(9.0f, 8.0f);
        glVertex2f(9.0f, 6.5f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(82, 37, 29);
        glVertex2f(0.5f, 2.4f);
        glVertex2f(0.5f, 2.8f);
        glVertex2f(0.6f, 2.8f);
        glVertex2f(0.6f, 2.4f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(82, 37, 29);
        glVertex2f(2.9f, 2.4f);
        glVertex2f(2.9f, 2.8f);
        glVertex2f(3.0f, 2.8f);
        glVertex2f(3.0f, 2.4f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(82, 37, 29);
        glVertex2f(5.9f, 2.4f);
        glVertex2f(5.9f, 2.8f);
        glVertex2f(6.0f, 2.8f);
        glVertex2f(6.0f, 2.4f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(82, 37, 29);
        glVertex2f(8.4f, 2.4f);
        glVertex2f(8.4f, 2.8f);
        glVertex2f(8.5f, 2.8f);
        glVertex2f(8.5f, 2.4f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(29, 82, 48);
        glVertex2f(0.3f, 2.8f);
        glVertex2f(0.6f, 3.3f);
        glVertex2f(0.8f, 2.8f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(29, 82, 48);
        glVertex2f(2.7f, 2.8f);
        glVertex2f(3.0f, 3.3f);
        glVertex2f(3.3f, 2.8f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(29, 82, 48);
        glVertex2f(5.7f, 2.8f);
        glVertex2f(6.0f, 3.3f);
        glVertex2f(6.3f, 2.8f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(29, 82, 48);
        glVertex2f(8.2f, 2.8f);
        glVertex2f(8.5f, 3.3f);
        glVertex2f(8.8f, 2.8f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 180, 17);
        glVertex2f(1.5f, 2.2f);
        glVertex2f(1.5f, 3.2f);
        glVertex2f(1.7f, 3.2f);
        glVertex2f(1.7f, 2.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 180, 17);
        glVertex2f(4.4f, 2.2f);
        glVertex2f(4.4f, 3.2f);
        glVertex2f(4.6f, 3.2f);
        glVertex2f(4.6f, 2.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(250, 180, 17);
        glVertex2f(7.4f, 2.2f);
        glVertex2f(7.4f, 3.2f);
        glVertex2f(7.6f, 3.2f);
        glVertex2f(7.6f, 2.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(64, 46, 6);
        glVertex2f(1.55f, 3.2f);
        glVertex2f(1.55f, 4.3f);
        glVertex2f(1.65f, 4.3f);
        glVertex2f(1.65f, 3.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(64, 46, 6);
        glVertex2f(4.45f, 3.2f);
        glVertex2f(4.45f, 4.3f);
        glVertex2f(4.55f, 4.3f);
        glVertex2f(4.55f, 3.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(64, 46, 6);
        glVertex2f(7.45f, 3.2f);
        glVertex2f(7.45f, 4.3f);
        glVertex2f(7.55f, 4.3f);
        glVertex2f(7.55f, 3.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(64, 46, 6);
        glVertex2f(0.9f, 4.8f);
        glVertex2f(0.9f, 4.9f);
        glVertex2f(1.6f, 4.3f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(64, 46, 6);
        glVertex2f(2.3f, 4.9f);
        glVertex2f(2.4f, 4.9f);
        glVertex2f(1.6f, 4.3f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(64, 46, 6);
        glVertex2f(3.5f, 4.8f);
        glVertex2f(3.5f, 4.9f);
        glVertex2f(4.5f, 4.3f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(64, 46, 6);
        glVertex2f(5.5f, 4.9f);
        glVertex2f(5.5f, 4.8f);
        glVertex2f(4.5f, 4.3f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(64, 46, 6);
        glVertex2f(6.5f, 4.9f);
        glVertex2f(6.5f, 4.8f);
        glVertex2f(7.5f, 4.3f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(64, 46, 6);
        glVertex2f(8.5f, 4.9f);
        glVertex2f(8.5f, 4.8f);
        glVertex2f(7.5f, 4.3f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(33, 23, 2);
        glVertex2f(0.9f, 5.2f);
        glVertex2f(0.9f, 6.1f);
        glVertex2f(1.0f, 6.1f);
        glVertex2f(1.0f, 5.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(33, 23, 2);
        glVertex2f(2.0f, 5.2f);
        glVertex2f(2.0f, 5.8f);
        glVertex2f(2.1f, 5.8f);
        glVertex2f(2.1f, 5.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(33, 23, 2);
        glVertex2f(6.1f, 5.2f);
        glVertex2f(6.1f, 5.8f);
        glVertex2f(6.2f, 5.8f);
        glVertex2f(6.2f, 5.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(33, 23, 2);
        glVertex2f(7.0f, 5.2f);
        glVertex2f(7.0f, 5.5f);
        glVertex2f(7.1f, 5.5f);
        glVertex2f(7.1f, 5.2f);
	glEnd();
	glBegin(GL_QUADS);
        glColor3ub(33, 23, 2);
        glVertex2f(7.7f, 5.2f);
        glVertex2f(7.7f, 5.5f);
        glVertex2f(7.8f, 5.5f);
        glVertex2f(7.8f, 5.2f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(47, 143, 23);
        glVertex2f(6.8f, 5.5f);
        glVertex2f(7.3f, 5.5f);
        glVertex2f(7.05f, 5.9f);
	glEnd();
	glBegin(GL_TRIANGLES);
        glColor3ub(47, 143, 23);
        glVertex2f(7.6f, 5.5f);
        glVertex2f(7.9f, 5.5f);
        glVertex2f(7.7f, 6.0f);
	glEnd();
	 int i;
    GLfloat p1=0.9f; 	//Value of x
    GLfloat q1= 4.9f; 	//Value of y
    GLfloat r1 = 0.27f;	//Radius
    int tringle2=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp2 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (252, 252, 252);
    glVertex2f (p1,q1);
    for(i= 0;i<=tringle2; i++)
    {
        glVertex2f (p1+(r1*cos(i*tp2/tringle2)), q1+(r1*sin(i*tp2/tringle2)));
    }
    glEnd ();
    GLfloat p2=2.4f; 	//Value of x
    GLfloat q2= 4.9f; 	//Value of y
    GLfloat r2 = 0.27f;	//Radius
    int tringle3=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp3 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (252, 252, 252);
    glVertex2f (p2,q2);
    for(i= 0;i<=tringle3; i++)
    {
        glVertex2f (p2+(r2*cos(i*tp3/tringle3)), q2+(r2*sin(i*tp3/tringle3)));
    }
    glEnd ();
     GLfloat p3=3.4f; 	//Value of x
    GLfloat q3= 4.95f; 	//Value of y
    GLfloat r3 = 0.27f;	//Radius
    int tringle4=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp4 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (252, 252, 252);
    glVertex2f (p3,q3);
    for(i= 0;i<=tringle4; i++)
    {
        glVertex2f (p3+(r3*cos(i*tp4/tringle4)), q3+(r3*sin(i*tp4/tringle4)));
    }
    glEnd ();
    GLfloat p4=5.5f; 	//Value of x
    GLfloat q4= 5.0f; 	//Value of y
    GLfloat r4 = 0.27f;	//Radius
    int tringle5=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp5 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (252, 252, 252);
    glVertex2f (p4,q4);
    for(i= 0;i<=tringle5; i++)
    {
        glVertex2f (p4+(r4*cos(i*tp5/tringle5)), q4+(r4*sin(i*tp5/tringle5)));
    }
    glEnd ();
    GLfloat p5=6.45f; 	//Value of x
    GLfloat q5= 4.95f; 	//Value of y
    GLfloat r5 = 0.27f;	//Radius
    int tringle6=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp6 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (252, 252, 252);
    glVertex2f (p5,q5);
    for(i= 0;i<=tringle6; i++)
    {
        glVertex2f (p5+(r5*cos(i*tp6/tringle6)), q5+(r5*sin(i*tp6/tringle6)));
    }
    glEnd ();

    GLfloat p6=8.6f; 	//Value of x
    GLfloat q6= 5.0f; 	//Value of y
    GLfloat r6 = 0.27f;	//Radius
    int tringle7=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp7 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (252, 252, 252);
    glVertex2f (p6,q6);
    for(i= 0;i<=tringle7; i++)
    {
        glVertex2f (p6+(r6*cos(i*tp7/tringle7)), q6+(r6*sin(i*tp7/tringle7)));
    }
    glEnd ();
    GLfloat p7=0.6f; 	//Value of x
    GLfloat q7= 6.0f; 	//Value of y
    GLfloat r7 = 0.3f;	//Radius
    int tringle8=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp8 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p7,q7);
    for(i= 0;i<=tringle8; i++)
    {
        glVertex2f (p7+(r7*cos(i*tp8/tringle8)), q7+(r7*sin(i*tp8/tringle8)));
    }
    glEnd ();
    GLfloat p8=0.5f; 	//Value of x
    GLfloat q8= 6.5f; 	//Value of y
    GLfloat r8 = 0.35f;	//Radius
    int tringle9=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp9 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p8,q8);
    for(i= 0;i<=tringle9; i++)
    {
        glVertex2f (p8+(r8*cos(i*tp9/tringle9)), q8+(r8*sin(i*tp9/tringle9)));
    }
    glEnd ();
    GLfloat p9=1.05f; 	//Value of x
    GLfloat q9= 6.55f; 	//Value of y
    GLfloat r9 = 0.38f;	//Radius
    int tringle10=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp10 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p9,q9);
    for(i= 0;i<=tringle10; i++)
    {
        glVertex2f (p9+(r9*cos(i*tp10/tringle10)), q9+(r9*sin(i*tp10/tringle10)));
    }
    glEnd ();
    GLfloat p10=1.5f; 	//Value of x
    GLfloat q10= 6.2f; 	//Value of y
    GLfloat r10 = 0.26f;	//Radius
    int tringle11=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp11 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p10,q10);
    for(i= 0;i<=tringle11; i++)
    {
        glVertex2f (p10+(r10*cos(i*tp11/tringle11)), q10+(r10*sin(i*tp11/tringle11)));
    }
    glEnd ();
    GLfloat p11=1.0f; 	//Value of x
    GLfloat q11= 6.2f; 	//Value of y
    GLfloat r11 = 0.43f;	//Radius
    int tringle12=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp12 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p11,q11);
    for(i= 0;i<=tringle12; i++)
    {
        glVertex2f (p11+(r11*cos(i*tp12/tringle12)), q11+(r11*sin(i*tp12/tringle12)));
    }
    glEnd ();
    GLfloat p12=1.8f; 	//Value of x
    GLfloat q12= 5.75f; 	//Value of y
    GLfloat r12 = 0.2f;	//Radius
    int tringle13=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp13 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p12,q12);
    for(i= 0;i<=tringle13; i++)
    {
        glVertex2f (p12+(r12*cos(i*tp13/tringle13)), q12+(r12*sin(i*tp13/tringle13)));
    }
    glEnd ();
    GLfloat p13=2.1f; 	//Value of x
    GLfloat q13= 5.9f; 	//Value of y
    GLfloat r13 = 0.32f;	//Radius
    int tringle14=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp14 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p13,q13);
    for(i= 0;i<=tringle14; i++)
    {
        glVertex2f (p13+(r13*cos(i*tp14/tringle14)), q13+(r13*sin(i*tp14/tringle14)));
    }
    glEnd ();
    GLfloat p14=2.3f; 	//Value of x
    GLfloat q14= 5.8f; 	//Value of y
    GLfloat r14 = 0.28f;	//Radius
    int tringle15=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp15 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p14,q14);
    for(i= 0;i<=tringle15; i++)
    {
        glVertex2f (p14+(r14*cos(i*tp15/tringle15)), q14+(r14*sin(i*tp15/tringle15)));
    }
    glEnd ();
    GLfloat p15=6.0f; 	//Value of x
    GLfloat q15= 5.8f; 	//Value of y
    GLfloat r15 = 0.29f;	//Radius
    int tringle16=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp16 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p15,q15);
    for(i= 0;i<=tringle16; i++)
    {
        glVertex2f (p15+(r15*cos(i*tp16/tringle16)), q15+(r15*sin(i*tp16/tringle16)));
    }
    glEnd ();
    GLfloat p16=6.2f; 	//Value of x
    GLfloat q16= 6.0f; 	//Value of y
    GLfloat r16 = 0.32f;	//Radius
    int tringle17=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp17 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p16,q16);
    for(i= 0;i<=tringle17; i++)
    {
        glVertex2f (p16+(r16*cos(i*tp17/tringle17)), q16+(r16*sin(i*tp17/tringle17)));
    }
    glEnd ();
    GLfloat p17=6.4f; 	//Value of x
    GLfloat q17= 5.8f; 	//Value of y
    GLfloat r17 = 0.25f;	//Radius
    int tringle18=100;	//Number of Triangle (More value means more smooth edge)

    GLfloat tp18 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (31, 92, 48);
    glVertex2f (p17,q17);
    for(i= 0;i<=tringle18; i++)
    {
        glVertex2f (p17+(r17*cos(i*tp18/tringle18)), q17+(r17*sin(i*tp18/tringle18)));
    }
    glEnd ();

    GLfloat p18=8.3f; 	//Sun
    GLfloat q18= 7.4f;
    GLfloat r18 = 0.365f;
    int tringle19=100;

    GLfloat tp19 =2.0f * PI;

    glBegin (GL_TRIANGLE_FAN);
    glColor3ub (240, 58, 55);
    glVertex2f (p18,q18);
    for(i= 0;i<=tringle19; i++)
    {
        glVertex2f (p18+(r18*cos(i*tp19/tringle19)), q18+(r18*sin(i*tp19/tringle19)));
    }
    glEnd ();











































    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900,800);

    glutCreateWindow("Colored House");

    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    gluOrtho2D(0,9,0,8);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
