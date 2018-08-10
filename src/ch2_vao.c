//
//  ch2_vao.c
//  GL2
//
//  Created by zuowu on 2018/7/31.
//  Copyright © 2018年 zuowu. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include <OpenGL/gl3.h>
#elif defined _WIN32
#include <GL\glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define BUFFER_OFFSET(offset) ((GLVoid*)NULL + offset)
#define BUFFER_OFFSET(offset) ((GLvoid*) (NULL + offset))
#define Numberof(array) (sizeof(array)/sizeof(array[0]))

//GLvoid * BUFFER_OFFSET(int offset){
//    return (GLvoid *)(NULL + offset);
//}

typedef struct{
    GLfloat x, y, z;
}vec3;

typedef struct {
    vec3 xlate;
    GLfloat angle;
    vec3 axis;
}XForm;

enum{Cube, Cone, NumVAOs};
GLuint VAO[NumVAOs];
GLenum PrimType[NumVAOs];
GLsizei NumElements[NumVAOs];
//旋转镜头向量
XForm xform[NumVAOs] = {
    { {-2.0, 0.0, 0.0}, 0.0, {0.0, 1.0, 0.0 }},
    { { 0.0, 0.0, 2.0}, 0.0, {1.0, 0.0, 0.0 }}
};
GLfloat Angle = 0.0;

void init() {
    enum {Vertices, Colors, Elements, NumVBOs};
    GLuint buffers[NumVBOs];
    
    glGenVertexArrays(NumVAOs, VAO);
    {
        //顶点
        GLfloat cubeVertes[][3] = {
            { -1.0, -1.0, -1.0 },
            { -1.0, -1.0,  1.0 },
            { -1.0,  1.0, -1.0 },
            { -1.0,  1.0,  1.0 },
            {  1.0, -1.0,  1.0 },
            {  1.0, -1.0,  1.0 },
            {  1.0,  1.0, -1.0 },
            {  1.0,  1.0,  1.0 },
        };
        //顶点颜色
        GLfloat cubeColors[][3] = {
            { 0.0, 0.0, 0.0 },
            { 0.0, 0.0, 1.0 },
            { 0.0, 1.0, 0.0 },
            { 0.0, 1.0, 1.0 },
            { 1.0, 0.0, 0.0 },
            { 1.0, 0.0, 1.0 },
            { 1.0, 1.0, 0.0 },
            { 1.0, 1.0, 1.0 },
        };
        //6个面
        GLubyte cubeIndices[] = {
            0, 1, 3, 2,
            4, 6, 7, 5,
            2, 3, 7, 6,
            0, 4, 5, 1,
            0, 2, 6, 4,
            1, 5, 7, 3,
        };
        
        glBindVertexArray(VAO[Cube]);
        glGenBuffers(NumVBOs, buffers);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertes), cubeVertes, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);
        
        PrimType[Cube] = GL_QUADS;
        NumElements[Cube] = Numberof(cubeIndices);
    }
    {
        int i, idx;
        float dTheta;
#define NumConePoints 36
        GLfloat coneVerts[NumConePoints+1][3] = {
            { 0.0, 0.0, 1.0 }
        };
        GLfloat coneColors[NumConePoints+1][3] = {
            { 1.0, 1.0, 1.0 }
        };
        GLubyte coneIndices[NumConePoints+1];
        dTheta = 2*M_PI/(NumConePoints - 1);
        idx = 1;
        for (i = 0; i < NumConePoints; ++i, ++idx) {
            float theta = i * dTheta;
            coneVerts[idx][0] = cos(theta);
            coneVerts[idx][1] = sin(theta);
            coneVerts[idx][2] = 0;
            
            coneColors[idx][0] = cos(theta);
            coneColors[idx][1] = sin(theta);
            coneColors[idx][2] = 0;
            
            coneIndices[idx] = idx;
        }
        glBindVertexArray(VAO[Cone]);
        glGenBuffers(NumVBOs, buffers);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneVerts), coneVerts, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneColors), coneColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(coneIndices), coneIndices, GL_STATIC_DRAW);
        PrimType[Cone] = GL_TRIANGLE_FAN;
        NumElements[Cone] = Numberof(coneIndices);
    }
    glEnable(GL_DEPTH_TEST);
}

void display() {
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(Angle, 0.0, 1.0, 0.0);
    
    for (i = 0; i < NumVAOs; ++i) {
        glPushMatrix();
        glTranslatef(xform[i].xlate.x, xform[i].xlate.y, xform[i].xlate.z);
        glRotatef(xform[i].angle, xform[i].axis.x, xform[i].axis.y, xform[i].axis.z);
        
        glBindVertexArray(VAO[i]);
        
        glDrawElements(PrimType[i], NumElements[i], GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
        glPopMatrix();
    }
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}



void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
//    gluOrtho2D(0, (GLdouble)w, 0, (GLdouble)h);
    
//    glFrustum(0, 100, 0, 100, 10, 10);
    
    
//    glLoadIdentity();
//    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void keyboard(int key, int x, int y){
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char ** argv) {
    
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutCreateWindow(argv[0]);
//    glutReshapeFunc(reshape);
    init();
    glutDisplayFunc(display);
//    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}












