#ifndef MAIN_H
#define MAIN_H
#if defined (__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include  <GL/glut.h>
#endif
#include <cstdio>
#include <istream>
#include <fstream>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
#define A 100
#define Time GLUT_BITMAP_TIMES_ROMAN_24
#define Helve GLUT_BITMAP_HELVETICA_18
#define Helve12 GLUT_BITMAP_HELVETICA_12
#define by9 GLUT_BITMAP_9_BY_15
#define by8 GLUT_BITMAP_8_BY_13
int screen_width = 800, screen_height = 800;
fstream myFile;
string fileName = "test.txt", resolStr = "15", orderString = "2", chooseCurve = "N/A", knotStr;
int MainWindow, GWin, curveType, moveCurve, movePoint, resolution = 15, degreeOrder = 2 , 
totalObjects, totalPoints, isKnotPosition = false;
bool isPointMove = false, addBSplinePoint = false, addBezierPoint = false, addBZcurve = false, 
addBScurve = false, mouseMove = false, chooseBZ = false, chooseBS = false, isKnotIn = false;
char toggle = 0; float r, g, b; 
void readFile();
void display();
void reDisplay();
void DrawBezierCurves();
void DrawBSplineCurves();
void deCasteljau(int resolution);
void reshape(int width, int height);
void keyBoardFunc(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void saveFile();

int GUIwin_width = 480, GUIwin_height = 700;
float getfloat(const string& str);
void GUIWinFunc();
void knotsWinFunc();
void GUIdisplay();
void renderString(const char* text, int length, int x, int y, int id);
void renderKnotString(void* format, const string& str, float num, char c);
void GUIMouseFunc(int button, int state, int x, int y);  
void GUIMotionFunc(int x, int y);
struct initialPoint{
    float x, y, r, g, b;
};
initialPoint PointObj;
void drawPointLine(initialPoint start, initialPoint end, int color, char c, int);
void drawapoint(initialPoint start,int color);
struct Bezier{
    vector<initialPoint> BezierPoints, BZtotalPoints;
    int index;
    void deCastelAlgo(int resolution);
};
struct BSpline{
    vector<initialPoint> BSplinePoints, BStotalPoints;
    vector<float> knotsVec;
    int index, k;
    float newKnot, position;
    bool knotVerify = false;
    float getKnots(int pos) const;
    void deBoorAlgo(int resolution);

};
vector<Bezier> BezierCurves;
vector<BSpline> BSplineCurves;

#endif