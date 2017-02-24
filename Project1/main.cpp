
//  Project1
//  Created by Dewan Choudhury.


#include<GLUT/GLUT.h>
#include<math.h>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <vector>


std::vector<GLfloat> xUsed;//stores the x-coordinates of the center of disks already drawn
std::vector<GLfloat> yUsed;//stores the y-coordinates of the center of disks already drawn

int numConcave = 3;
int numConvex = 3;

//used to ensure same number of both disks are drawn
bool diskType(){
    int r = rand()%2;
    if(r==1 && numConcave>0){
        numConcave--;
        return true;
    }
    if(r==1 && numConcave==0){
        numConvex--;
        return false;
    }
    if(r==0 && numConvex==0){
        numConcave--;
        return true;
    }
    numConvex--;
    return false;
}


//this method checks whether using the given coordinates will create overlapping disks
bool overlaps(GLfloat xCoord,GLfloat yCoord){
    for(int i=0;i<xUsed.size();i++){
        GLfloat distance = (GLfloat)sqrt( ((xUsed[i]-xCoord)*(xUsed[i]-xCoord)) + ((yUsed[i]-yCoord)*(yUsed[i]-yCoord)) );
        
        if(distance<=0.5){
            return true;
        }
    }
    return false;
}

//generates random double values
double randDouble(double min, double max){
    double ans = (double)rand()/ RAND_MAX;
    return min + ans * (max-min);
}

//lays out colored lines horizontally to form disk
void circle(bool concave,GLfloat x,GLfloat y){
    GLfloat r = 0.25;
    double t, p = 3.141593 / 180;
    GLfloat deduction = 0.0;
    for (double i = 0; i < 90;i = i + 0.5){
        t = i*p;
        GLfloat x1 = x+r*cos(t);
        GLfloat y1 = y+r*sin(t);
        GLfloat x2 = x-r*cos(t);
        GLfloat y2 = y1;
        if(concave){
            glColor3f(0.5-deduction, 0.5-deduction, 0.5-deduction);
        }else{
            glColor3f(0.5+deduction, 0.5+deduction, 0.5+deduction);

        }
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);

        GLfloat x3 = x+r*cos(t);
        GLfloat y3 = y-r*sin(t);
        GLfloat x4 = x+r*-cos(t);
        GLfloat y4 = y3;
        if(concave){
            glColor3f(0.5+deduction, 0.5+deduction, 0.5+deduction);
        }else{
            glColor3f(0.5-deduction, 0.5-deduction, 0.5-deduction);
            
        }
        glVertex2f(x3,y3);
        glVertex2f(x4,y4);
        
        deduction +=(0.5/180.0);
    }//for
}


void display(void){
    int numOfDisks = 6;
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_LINES);
    
    for(int i = 0;i<numOfDisks;i++){
        double xValue = randDouble(-1.50, 1.5);
        double yValue = randDouble(-1.25, 1.25);
        if(xUsed.size()!=0){
            while(overlaps(xValue,yValue)){//used to avoid overlapping
                xValue = randDouble(-1.50, 1.5);
                yValue = randDouble(-1.25, 1.25);
            }
        }
        xUsed.push_back(xValue);
        yUsed.push_back(yValue);
        bool concave = diskType();
        circle(concave,xValue,yValue);
    }
    
    glEnd();
    glFlush();
}


int main(int argc, char ** argv){
    srand(time(NULL));
    glutInit(& argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,300);
    glutInitWindowPosition(200,100);
    glutCreateWindow("Concave & Convex Illusion");
    gluOrtho2D(-2.0,2.0,-1.5,1.5);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}