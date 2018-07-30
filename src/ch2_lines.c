//
//  ch2_lines.c
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

#define drawOneLine(x1, y1, x2, y2) \
glBegin(GL_LINES);                  \
glVertex2f((x1),(y1));              \
glVertex2f((x2),(y2));              \
glEnd();

void display(){
    int i;
    
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    
    /* in 1st row, 3 lines, each with a different stipple  */
    glEnable (GL_LINE_STIPPLE);
    
    glLineStipple (1, 0x0101);  /*  dotted  */
    drawOneLine (50.0, 125.0, 150.0, 125.0);
    glLineStipple (1, 0x00FF);  /*  dashed  */
    drawOneLine (150.0, 125.0, 250.0, 125.0);
    glLineStipple (1, 0x1C47);  /*  dash/dot/dash  */
    drawOneLine (250.0, 125.0, 350.0, 125.0);
    
    /* in 2nd row, 3 wide lines, each with different stipple */
    glLineWidth (5.0);
    glLineStipple (1, 0x0101);  /*  dotted  */
    drawOneLine (50.0, 100.0, 150.0, 100.0);
    glLineStipple (1, 0x00FF);  /*  dashed  */
    drawOneLine (150.0, 100.0, 250.0, 100.0);
    glLineStipple (1, 0x1C47);  /*  dash/dot/dash  */
    drawOneLine (250.0, 100.0, 350.0, 100.0);
    glLineWidth (1.0);
    
    /* in 3rd row, 6 lines, with dash/dot/dash stipple  */
    /* as part of a single connected line strip         */
    glLineStipple (1, 0x1C47);  /*  dash/dot/dash  */
    glBegin (GL_LINE_STRIP);
    for (i = 0; i < 7; i++)
        glVertex2f (50.0 + ((GLfloat) i * 50.0), 75.0);
    glEnd ();
    
    /* in 4th row, 6 independent lines with same stipple  */
    for (i = 0; i < 6; i++) {
        drawOneLine (50.0 + ((GLfloat) i * 50.0), 50.0, 50.0 + ((GLfloat)(i+1) * 50.0), 50.0);
    }
    
    /* in 5th row, 1 line, with dash/dot/dash stipple    */
    /* and a stipple repeat factor of 5                  */
    glLineStipple (5, 0x1C47);  /*  dash/dot/dash  */
    drawOneLine (50.0, 25.0, 350.0, 25.0);
    glDisable (GL_LINE_STIPPLE);
//    * `void glPolygonMode(GLenum face, GLenum mode)` face : `GL_PRONT_AND_BACK`(3.1只有这个),`GL_FRONT`,`GL_BACK`  mode : `GL_POINT`,`GL_LINE`,`GL_FILL`
//    * `void glFrontFace(GLenum mode)`:设定多边形正反面 mode : `GL_CCW`逆时针正面,`GL_CW`顺时针正面
//    * `void glCullFace(GLenum mode)` : 剔除 mode : `GL_FRONT`,`GL_BACK`,`GL_FRONT_AND_BACK`, `glEnable(GL_CULL_FACE)`启动剔除功能,`glDisable(GL_CULL_FACE)`禁用
    
    glColor3f(1.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glBegin(GL_POLYGON);
    glVertex2d(400, 100);
    glVertex2d(450, 100);
    glVertex2d(450, 150);
    glVertex2d(400, 150);
    glVertex2d(350, 150);
    glVertex2d(350, 100);
    glVertex2d(350, 50);
    glVertex2d(400, 50);
    glVertex2d(450, 50);
    glVertex2d(450, 100);
    glEnd();
    
    glFlush ();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLsizei)w, 0.0, (GLsizei)h);
}

int main(int argc, char ** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RED);
    glutInitWindowSize(800, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
















