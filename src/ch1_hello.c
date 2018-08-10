//
//  main.c
//  ch1
//
//  Created by zuowu on 2018/6/29.
//  Copyright © 2018年 zuowu. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#elif defined _WIN32
#include <GL\glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, 0.75, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    glFlush();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void reshape(int width, int height){
    printf("reshape --\n");
}
void keyboard(int key, int x, int y){
    printf("keyboard key = %d, mouse pos = (%d, %d)\n", key,x,y);
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char ** argv) {
    // insert code here...
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    //不写不会调用keyboard 和 mouse 回调
    glutReshapeFunc(reshape);
    //键盘回调 会传入鼠标位置 .....
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}















