//
//  ch2_reshape.c
//  GL2
//
//  Created by zuowu on 2018/7/27.
//  Copyright © 2018年 zuowu. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#elif defined _WIN32
#include <GL\glut.h>
#endif
#include <stdio.h>

void reshape(int w, int h) {
    //画布占据 0 0 w h 范围
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    //设定坐标系统
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //设定左下为00
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char ** argv) {
    return 0;
}
