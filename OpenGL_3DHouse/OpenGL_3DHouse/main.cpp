//
//  main.cpp
//  OpenGL_3DHouse
//
//  Created by Yu Tian on 4/30/16.
//  Copyright © 2016 Yu Tian. All rights reserved.
//

#include <iostream>

#include <stdlib.h>
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include "imageloader.hpp"
// model == 1 : daytime, model == 2 : daytime & night
#define model 1

float _angle = 0.0;
float zFac = 0.0;
GLboolean ch_rotate = false;
GLuint  _textureBrick, _textureDoor, _textureGrass, _textureRoof, _textureWindow, _textureSky,
        _textureWall1, _textureWall1w, _textureWall2, _textureWall2w, _textureWall3, _textureWall3w,
        _textureWall4, _textureWall4w, _textureWall5, _textureWall5w, _textureWall6, _textureWall6w,
        _textureWall7, _textureWall7w, _textureWall8, _textureRoofing1, _textureRoofing2, _textureWater,
        _textureFloor1, _textureFloor2, _textureStonePath, _textureFence, _textureTree, _textureOcean;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle() {
    glutPostRedisplay();   // Post a re-paint request to activate display()
}

void renderScene(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    
    // Sky
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureSky);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-10);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-10,10,0);
    glTexCoord3f(1.0,1.0,0.1);  glVertex3f(10,10,0);
    glTexCoord3f(1.0,0.0,0.1);  glVertex3f(10,-10,0);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-10,-10,0);
    glEnd();
    glPopMatrix();
    
    // Grass
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureGrass);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0,70.0,1);  glVertex3f(-3,-1.5,3);
    glTexCoord3f(0.0,0.0,-1);  glVertex3f(-3,-1.5,-3);
    glTexCoord3f(70.0,0.0,-1);  glVertex3f(3,-1.5,-3);
    glTexCoord3f(70.0,70.0,1);  glVertex3f(3,-1.5,3);
    glEnd();
    glPopMatrix();
    
    // Ocean
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureOcean);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0,70.0,1);  glVertex3f(-30,-1.52,5);
    glTexCoord3f(0.0,0.0,-1);  glVertex3f(-30,-1.52,-5);
    glTexCoord3f(70.0,0.0,-1);  glVertex3f(30,-1.52,-5);
    glTexCoord3f(70.0,70.0,1);  glVertex3f(30,-1.52,5);
    glEnd();
    glPopMatrix();

    // House base
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureFloor2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-2,-1.499,1);
    glTexCoord3f(1.0,1.0,0.1);  glVertex3f(2,-1.499,1);
    glTexCoord3f(1.0,0.0,0.1);  glVertex3f(2,-1.499,-1);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.499,-1);
    glEnd();
    glPopMatrix();
    
    // Front side
    // front side upper left
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall3w);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-2,0,1);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(0,0,1);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(0,-0.75,1);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-0.75,1);
    glEnd();
    glPopMatrix();
    
    // front side upper right
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall4w);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(0,0,1);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(2,0,1);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(2,-0.75,1);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(0,-0.75,1);
    glEnd();
    glPopMatrix();
    
    // front side bottom left
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-2,-0.75,1);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(0,-0.75,1);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(0,-1.5,1);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,1);
    glEnd();
    glPopMatrix();
    
    // front side bottom left
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(0,-0.75,1);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(2,-0.75,1);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(2,-1.5,1);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(0,-1.5,1);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    
    glBindTexture(GL_TEXTURE_2D, _textureRoof);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // Roof
    glTexCoord3f(0.0,2.0,0); glVertex3f(-2.05,0.5,0);
    glTexCoord3f(4.0,2.0,0);glVertex3f(2.05,0.5,0);
    glTexCoord3f(4.0,0.0,1.25); glVertex3f(2.05,-0.1,1.25);
    glTexCoord3f(0.0,0.0,1.25); glVertex3f(-2.05,-0.1,1.25);
    glEnd();
    glPopMatrix();
    

    glPushMatrix();
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, _textureDoor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // Door
    glTexCoord3f(0.0,1.0,1.0001); glVertex3f(0.2,-1.5,1.0001);
    glTexCoord3f(2.0,1.0,1.0001); glVertex3f(0.8,-1.5,1.0001);
    glTexCoord3f(2.0,0.0,1.0001); glVertex3f(0.8,-1.0,1.0001);
    glTexCoord3f(0.0,0.0,1.0001); glVertex3f(0.2,-1.0,1.0001);
    glEnd();
    glPopMatrix();
    
    // Back side
    // Back side right top
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureWall2w);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,-1);  glVertex3f(-2,0,-1);
    glTexCoord3f(2.0,1.0,-1);  glVertex3f(0,0,-1);
    glTexCoord3f(2.0,0.0,-1);  glVertex3f(0,-0.75,-1);
    glTexCoord3f(0.0,0.0,-1);  glVertex3f(-2,-0.75,-1);
    glEnd();
    glPopMatrix();
    
    // back side left top
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureWall1w);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,-1);  glVertex3f(0,0,-1);
    glTexCoord3f(2.0,1.0,-1);  glVertex3f(2,0,-1);
    glTexCoord3f(2.0,0.0,-1);  glVertex3f(2,-0.75,-1);
    glTexCoord3f(0.0,0.0,-1);  glVertex3f(0,-0.75,-1);
    glEnd();
    glPopMatrix();
    
    // back side right bottom
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureWall2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,-1);  glVertex3f(-2,-0.75,-1);
    glTexCoord3f(2.0,1.0,-1);  glVertex3f(0,-0.75,-1);
    glTexCoord3f(2.0,0.0,-1);  glVertex3f(0,-1.5,-1);
    glTexCoord3f(0.0,0.0,-1);  glVertex3f(-2,-1.5,-1);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureWall1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,-1);  glVertex3f(0,-0.75,-1);
    glTexCoord3f(1.0,1.0,-1);  glVertex3f(2,-0.75,-1);
    glTexCoord3f(1.0,0.0,-1);  glVertex3f(2,-1.5,-1);
    glTexCoord3f(0.0,0.0,-1);  glVertex3f(0,-1.5,-1);
    glEnd();
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    
    glBindTexture(GL_TEXTURE_2D, _textureRoof);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // Roof
    glTexCoord3f(0.0,2.0,0); glVertex3f(-2.05,0.5,0);
    glTexCoord3f(4.0,2.0,0);glVertex3f(2.05,0.5,0);
    glTexCoord3f(4.0,0.0,-1.25); glVertex3f(2.05,-0.1,-1.25);
    glTexCoord3f(0.0,0.0,-1.25); glVertex3f(-2.05,-0.1,-1.25);
    glEnd();

    glPopMatrix();
    
    // Right side
    // right top
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall5w);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,1); glVertex3f(2,0,1);
    glTexCoord3f(2.0,1.0,-1); glVertex3f(2,0,-1);
    glTexCoord3f(2.0,0.0,-1); glVertex3f(2,-0.75,-1);
    glTexCoord3f(0.0,0.0,1); glVertex3f(2,-0.75,1);
    glEnd();
    glPopMatrix();
    
    // right bottom
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,1); glVertex3f(2,-0.75,1);
    glTexCoord3f(2.0,1.0,-1); glVertex3f(2,-0.75,-1);
    glTexCoord3f(2.0,0.0,-1); glVertex3f(2,-1.5,-1);
    glTexCoord3f(0.0,0.0,1); glVertex3f(2,-1.5,1);
    glEnd();
    glPopMatrix();
    
    // right top triangle
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);  // Wall Upper
    glTexCoord3f(0.0,1.0,0); glVertex3f(2,0.5,0);
    glTexCoord3f(1.0,0.0,1); glVertex3f(2,0,1);
    glTexCoord3f(-1.0,0.0,-1); glVertex3f(2,0,-1);
    glEnd();
    glPopMatrix();
    
    // Left side
    // left side top
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall6w);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,1);    glVertex3f(-2,0,1);
    glTexCoord3f(2.0,1.0,-1);    glVertex3f(-2,0,-1);
    glTexCoord3f(2.0,0.0,-1);    glVertex3f(-2,-0.75,-1);
    glTexCoord3f(0.0,0.0,1);    glVertex3f(-2,-0.75,1);
    glEnd();
    glPopMatrix();
    
    // left side bottom
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,1);    glVertex3f(-2,-0.75,1);
    glTexCoord3f(2.0,1.0,-1);    glVertex3f(-2,-0.75,-1);
    glTexCoord3f(2.0,0.0,-1);    glVertex3f(-2,-1.5,-1);
    glTexCoord3f(0.0,0.0,1);    glVertex3f(-2,-1.5,1);
    glEnd();
    glPopMatrix();
    
    
    // left top triangle
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWall6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);  // Wall Upper
    glTexCoord3f(0.0,1.0,0);    glVertex3f(-2,0.5,0);
    glTexCoord3f(1.0,0.0,1);    glVertex3f(-2,0,1);
    glTexCoord3f(-1.0,0.0,-1);    glVertex3f(-2,0,-1);
    glEnd();
    glPopMatrix();
    
    // extented part
    // stone path
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureStonePath);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,2.0,1);    glVertex3f(-2,-1.499,-1);
    glTexCoord3f(4.0,2.0,-1);    glVertex3f(2,-1.499,-1);
    glTexCoord3f(4.0,0.0,-1);    glVertex3f(2,-1.499,-2);
    glTexCoord3f(0.0,0.0,1);    glVertex3f(-2,-1.499,-2);
    glEnd();
    glPopMatrix();
    
    // swimming pool
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureWater);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,1);    glVertex3f(0.25,-1.498,-1.75);
    glTexCoord3f(2.0,1.0,-1);    glVertex3f(1.75,-1.498,-1.75);
    glTexCoord3f(2.0,0.0,-1);    glVertex3f(1.75,-1.498,-1.25);
    glTexCoord3f(0.0,0.0,1);    glVertex3f(0.25,-1.498,-1.25);
    glEnd();
    glPopMatrix();
    

    // roof of swimming pool
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureRoofing1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,1);    glVertex3f(2,-0.8,-1);
    glTexCoord3f(2.0,1.0,-1);    glVertex3f(2,-1,-2);
    glTexCoord3f(2.0,0.0,-1);    glVertex3f(0,-1,-2);
    glTexCoord3f(0.0,0.0,1);    glVertex3f(0,-0.8,-1);
    glEnd();
    glPopMatrix();
    
    // back side door
    glPushMatrix();
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, _textureDoor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);  // Door
    glTexCoord3f(0.0,1.0,1.0001); glVertex3f(-0.8,-1.0,-1.0001);
    glTexCoord3f(1.0,1.0,1.0001); glVertex3f(-0.5,-1.0,-1.0001);
    glTexCoord3f(1.0,0.0,1.0001); glVertex3f(-0.5,-1.5,-1.0001);
    glTexCoord3f(0.0,0.0,1.0001); glVertex3f(-0.8,-1.5,-1.0001);
    glEnd();
    glPopMatrix();
    
    // front fence
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureFence);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(2,-0.75,1.5);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(2,-0.75,1);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(2,-1.5,1);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(2,-1.5,1.5);
    glEnd();
    
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-2,-0.75,1.5);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(-2,-0.75,1);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(-2,-1.5,1);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,1.5);
    glEnd();
    
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-2,-0.75,1.5);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(-1,-0.75,1.5);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(-1,-1.5,1.5);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,1.5);
    glEnd();
    
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(2,-0.75,1.5);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(1,-0.75,1.5);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(1,-1.5,1.5);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(2,-1.5,1.5);
    glEnd();
    glPopMatrix();
    
    // front stone path
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureStonePath);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,2.0,1);    glVertex3f(-2,-1.499,1);
    glTexCoord3f(4.0,2.0,-1);    glVertex3f(2,-1.499,1);
    glTexCoord3f(4.0,0.0,-1);    glVertex3f(2,-1.499,1.5);
    glTexCoord3f(0.0,0.0,1);    glVertex3f(-2,-1.499,1.5);
    glEnd();
    glPopMatrix();
    
    // back side fence
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureFence);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    glRotatef(_angle + zFac, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(2,-0.75,-2);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(2,-0.75,-1);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(2,-1.5,-1);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(2,-1.5,-2);
    glEnd();
    
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-2,-0.75,-2);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(-2,-0.75,-1);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(-2,-1.5,-1);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,-2);
    glEnd();
    
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-2,-0.75,-2);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(-1,-0.75,-2);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(-1,-1.5,-2);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,-2);
    glEnd();
    
    glBegin(GL_QUADS);  // Wall
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-2,-0.75,-2);
    glTexCoord3f(2.0,1.0,0.1);  glVertex3f(-1,-0.75,-2);
    glTexCoord3f(2.0,0.0,0.1);  glVertex3f(-1,-1.5,-2);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,-2);
    glEnd();

    glPopMatrix();
    
    // auto rotate factor
    if (ch_rotate) {
        zFac += 0.5;
    }
    glutSwapBuffers();
    
    
}

void mySpecialFunc(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_RIGHT:
            _angle += 1;
            if (_angle > 360) _angle = 0.0;
            break;
        case GLUT_KEY_LEFT:
            _angle -= 1;
            if (_angle > 360) _angle = 0.0;
            break;
        case ' ':
            ch_rotate = !ch_rotate;
            if (ch_rotate) {
                glutIdleFunc(idle);
            } else {
                glutIdleFunc(NULL);
            }
            break;
            
    }
    glutPostRedisplay();
}

GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    
    Image* image = loadBMP("bricks.bmp");
    _textureBrick = loadTexture(image);
    image = loadBMP("door0.bmp");
    _textureDoor = loadTexture(image);
    image = loadBMP("grass.bmp");
    _textureGrass = loadTexture(image);
    image = loadBMP("grassmatroofing.bmp");
    _textureRoof = loadTexture(image);
    image = loadBMP("trim.bmp");
    _textureWindow = loadTexture(image);
    image = loadBMP("sky.bmp");
    _textureSky = loadTexture(image);
    image = loadBMP("wallpaper1.bmp");
    _textureWall1 = loadTexture(image);
    image = loadBMP("wallpaper1windows.bmp");
    _textureWall1w = loadTexture(image);
    image = loadBMP("wallpaper2.bmp");
    _textureWall2 = loadTexture(image);
    image = loadBMP("wallpaper2windows.bmp");
    _textureWall2w = loadTexture(image);
    image = loadBMP("wallpaper3.bmp");
    _textureWall3 = loadTexture(image);
    image = loadBMP("wallpaper3windows.bmp");
    _textureWall3w = loadTexture(image);
    image = loadBMP("wallpaper4.bmp");
    _textureWall4 = loadTexture(image);
    image = loadBMP("wallpaper4windows.bmp");
    _textureWall4w = loadTexture(image);
    image = loadBMP("wallpaper5.bmp");
    _textureWall5 = loadTexture(image);
    image = loadBMP("wallpaper5windows.bmp");
    _textureWall5w = loadTexture(image);
    image = loadBMP("wall1.bmp");
    _textureWall6 = loadTexture(image);
    image = loadBMP("wall1windows.bmp");
    _textureWall6w = loadTexture(image);
    image = loadBMP("wall2.bmp");
    _textureWall7 = loadTexture(image);
    image = loadBMP("wall2windows.bmp");
    _textureWall7w = loadTexture(image);
    image = loadBMP("wall3.bmp");
    _textureWall8 = loadTexture(image);
    image = loadBMP("roofing.bmp");
    _textureRoofing1 = loadTexture(image);
    image = loadBMP("roofing2.bmp");
    _textureRoofing2 = loadTexture(image);
    image = loadBMP("flooring.bmp");
    _textureFloor1 = loadTexture(image);
    image = loadBMP("flooring2.bmp");
    _textureFloor2 = loadTexture(image);
    image = loadBMP("water.bmp");
    _textureWater = loadTexture(image);
    image = loadBMP("stonepath.bmp");
    _textureStonePath = loadTexture(image);
    image = loadBMP("fence.bmp");
    _textureFence = loadTexture(image);
    image = loadBMP("tree.bmp");
    _textureTree = loadTexture(image);
    image = loadBMP("ocean.bmp");
    _textureOcean = loadTexture(image);

    delete image;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1200,1200);
    glutCreateWindow("Textured House by Yu Tian");
    glEnable(GL_DEPTH_TEST);
    glutIdleFunc(idle);
    glutReshapeFunc(resize);
    glutSpecialFunc(mySpecialFunc);
    glutDisplayFunc(renderScene);
    Initialize();
    
    if (model == 2) {
        /* set up depth-buffering */
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        /* turn on default lighting */
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        /* define the projection transformation */
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(40,1,4,20);
        /* define the viewing transformation */
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(5.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
        
        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    }
    
    glutMainLoop();
    
    return 0;
}
