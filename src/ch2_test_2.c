//
//  ch2_test_2.c
//  GL2
//
//  Created by zuowu on 2018/8/1.
//  Copyright © 2018年 zuowu. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <stdlib.h>

#define X .525731112119133606
#define Z .850650808352039932

void normalize(float v[3]){
    GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
}

void normcrossprod(float v1[3], float v2[3], float out[3]){
    out[0] = v1[1]*v2[2] - v1[2]*v2[1];
    out[1] = v1[2]*v2[0] - v1[0]*v2[2];
    out[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

void display(void)
{
    /*清楚所有的像素*/
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glLoadIdentity();//将当前矩阵设置为单位矩阵
    gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
    glScalef(1.0,2.0,1.0);
    glutWireCube(1.0);
    /*不等待
     马上开始处理保存在缓冲区中的OpenGL函数调用*/
    
    
    
//    unsigned VAO_CUBE;
//    GLuint buffers[3];
//    GLfloat cubeVertes[][3] = {
//        { -1.0, -1.0, -1.0 },
//        { -1.0, -1.0,  1.0 },
//        { -1.0,  1.0, -1.0 },
//        { -1.0,  1.0,  1.0 },
//        {  1.0, -1.0,  1.0 },
//        {  1.0, -1.0,  1.0 },
//        {  1.0,  1.0, -1.0 },
//        {  1.0,  1.0,  1.0 },
//    };
//
//    GLfloat cubeColors[][3] = {
//        { 0.0, 0.0, 0.0},
//        { 0.0, 0.0, 1.0},
//        { 0.0, 1.0, 0.0},
//        { 0.0, 1.0, 1.0},
//        { 1.0, 0.0, 0.0},
//        { 1.0, 0.0, 1.0},
//        { 1.0, 1.0, 0.0},
//        { 1.0, 1.0, 1.0},
//    };
//
//    GLubyte cubeInddices[] = {
//        0, 1, 3, 2,
//        4, 6, 7, 5,
//        2, 3, 7, 6,
//        0, 4, 5, 1,
//        0, 2, 6, 4,
//        1, 5, 7, 3,
//    };
//
//
//
//    glGenBuffers(3, buffers);
//    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertes), cubeVertes, GL_STATIC_DRAW);
//    glVertexPointer(3, GL_FLOAT, 0, cubeVertes);
//    glEnableClientState(GL_VERTEX_ARRAY);
//
//    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
//    glColorPointer(3, GL_FLOAT, 0, cubeColors);
//    glEnableClientState(GL_COLOR_ARRAY);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_APPLE, buffers[2]);
//    glBufferData(GL_ELEMENT_ARRAY_APPLE, sizeof(cubeInddices), cubeInddices, GL_STATIC_DRAW);
//
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//
//    glBindVertexArrayAPPLE(VAO_CUBE);
//    glDrawElements(GL_QUADS, 6, GL_UNSIGNED_BYTE, cubeInddices);
    
    static GLfloat vdata[12][3] = {
        {  -X, 0.0,  Z },{   X, 0.0,   Z },{  -X, 0.0,  -Z}, {   X, 0.0,  -Z},
        { 0.0,  Z,   X },{ 0.0,   Z,  -X },{ 0.0,  -Z,   X}, { 0.0,  -Z,  -X},
        {   Z,  X, 0.0 },{  -Z,   X, 0.0 },{   Z,  -X, 0.0}, {  -Z,  -X, 0.0},
    };
    
    static GLuint tindices [20][3] = {
        { 1, 4, 0 }, { 4, 9, 0 }, { 4, 9, 5 }, { 8, 5, 4 }, { 1, 8, 4 },
        { 1,10, 8 }, {10, 3, 8 }, { 8, 3, 5 }, { 3, 2, 5 }, { 3, 7, 2 },
        { 3,10, 7 }, {10, 6, 7 }, { 6,11, 7 }, { 6, 0,11 }, { 6, 1, 0 },
        {10, 1, 6 }, {11, 0, 9 }, { 2,11, 9 }, { 5, 2, 9 }, {11, 2, 7 },
    };
    
    glBegin(GL_TRIANGLES);
    for (int i = 0 ; i < 20 ; i++) {
        
        GLfloat d1[3], d2[3], norm[3];
        for (int j = 0 ; j < 3 ; j++) {
            d1[j] = vdata [tindices[i][0]] [j] - vdata [tindices[i][1]] [j];
            d2[j] = vdata [tindices[i][1]] [j] - vdata [tindices[i][2]] [j];
        }
        normcrossprod(d1, d2, norm);
        glNormal3fv(norm);
        
        glVertex3fv(&vdata[tindices[i][0]][0]);
        glVertex3fv(&vdata[tindices[i][1]][0]);
        glVertex3fv(&vdata[tindices[i][2]][0]);
    }
    glEnd();
    
    glFlush();
}
void init(void)
{
    /*指定清楚颜色*/
    glClearColor(0.0,0.0,0.0,0.0);
    /*初始化视景体*/
    glShadeModel(GL_FLAT);
}
void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei) w,(GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
