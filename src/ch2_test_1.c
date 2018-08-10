//
//  ch2_test_1.c
//  GL2
//
//  Created by zuowu on 2018/7/31.
//  Copyright © 2018年 zuowu. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#elif defined _WIN32
#include <GL\glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600


void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, (GLdouble)w, 0, (GLdouble)h);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex3f(100.0, 100.0, 0.0);
    glColor3f(1, 1, 0);
    glVertex3f(200.0, 100.0, 0.0);
    glColor3f(1, 0, 0);
    glVertex3f(200.0, 200.0, 0.0);
    glColor3f(0, 0, 1);
    glVertex3f(100.0, 200.0, 0.0);
    glEnd();
    
    const int n = 360;
    GLfloat rcx = 300;
    GLfloat rcy = 150;
    GLfloat radius = 50;
    glBegin(GL_POLYGON);
    
    for (GLint i = 0 ; i < n ; i++) {
        glColor3f((rand()%100)/100.0, (rand()%100)/100.0, (rand()%100)/100.0);
        GLfloat x = rcx + sin(((GLfloat)i)/n*2*M_PI) * radius;
        GLfloat y = rcy + cos(((GLfloat)i)/n*2*M_PI) * radius;
        glVertex3f(x, y, 0);
    }
    glEnd();

    
    
//    static GLfloat intertwined[] = {
//        1.0, 0.2, 1.0, 100.0, 100.0, 0.0,
//        1.0, 0.2, 0.2, 0.0, 200.0, 0.0,
//        1.0, 1.0, 0.2, 100.0, 300.0, 0.0,
//        0.2, 1.0, 0.2, 200.0, 300.0, 0.0,
//        0.2, 1.0, 1.0, 300.0, 200.0, 0.0,
//        0.2, 0.2, 1.0, 200.0, 100.0, 0.0
//    };
//    glInterleavedArrays(GL_C3F_V3F, 0, intertwined);

    static GLfloat intertwined[] = {
        1.0, 0.0, 0.0, 400.0, 100.0, 0.0,
        0.0, 1.0, 0.0, 600.0, 100.0, 0.0,
        0.0, 0.0, 1.0, 500.0, 200.0, 0.0
    };
    glInterleavedArrays(GL_C3F_V3F, 0, intertwined);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glFlush();

}



void keybroad(unsigned char key, int x, int y){
    if (key == 27) {
        exit(0);
    }
}

void mouse(int key, int state, int x, int y){
//    printf("key = %d, state = %d, x = %d, y = %d\n", key, state, x, y);
}

int main(int argc, char ** argv) {
    
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keybroad);
    glutMainLoop();
    return 0;
}
