#include "main.h"
#include "B_Spline.cpp"
#include "Bezier.cpp"
#include "getDataFromFile.cpp"
using namespace std;

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(screen_width,screen_height);
	glutInitWindowPosition(50, 50);
	MainWindow = glutCreateWindow("Project-4");
	glClearColor(0, 0, 0, 1); 
	readFile();
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyBoardFunc); 
	glutReshapeFunc(reshape);   
	glutMouseFunc(mouse);    
	glutMotionFunc(motion);   
	glutInitWindowSize(GUIwin_width, GUIwin_height);
	glutInitWindowPosition( screen_width + 100, 70);
	GWin = glutCreateWindow("GUI-Window");
	glClearColor(0,0.15, 0.25, 1);
	glutDisplayFunc(GUIdisplay);
	glutKeyboardFunc(keyBoardFunc);
	glutMouseFunc(GUIMouseFunc);
	glutMainLoop();
	return 0;
}
void reDisplay(){
	glutPostWindowRedisplay(MainWindow);
	glutPostWindowRedisplay(GWin);
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	 DrawBezierCurves();
	 DrawBSplineCurves();
    glFlush();
}
void GUIdisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if(toggle){
		glClearColor(0.02,0.2,0.1,0);
		gluOrtho2D(0, 1, 0, 40);
		knotsWinFunc();
		glutSwapBuffers();
	}
	else{
		glClearColor(0,0.15, 0.25, 1);
		GUIWinFunc();
	}
	glFlush();  
}
void GUIWinFunc(){
   	string str = "Bezier (Blue) <==> B-spline (Green)";
	glColor3f(0.4,1.0,0.9);
   	renderString(str.data(), str.size(), 40, 380, 0);

	string str6 = "Modify Point (drag point with mouse)         Selected Curve(Red):";
	glColor3f(1,1,1.0);
   	renderString(str6.data(), str6.size(), 10, 355, 1);
	glColor3f(1,0.0,0.0);
	renderString(chooseCurve.data(), chooseCurve.size(), 320, 352, 0);

    string str2 = "Create New Curve";
	glColor3f(1,0.5,0.2);
    renderString(str2.data(), str2.size(), 10, 330, 0);
    string str1 = "Press Z: New Bezier Point";
	glColor3f(1,1,1.0);
    renderString(str1.data(), str1.size(), 10, 315, 1);
	string strDrop = "(Drop Anywhere on Screen)";
	glColor3f(1,1,1.0);
    renderString(strDrop.data(), strDrop.size(), 190, 305, 1);
    string str3 = "Press S: New B-Spline Point";
	glColor3f(1,1,1);
    renderString(str3.data(), str3.size(), 10, 295, 1);

	string str7 = "Add / Remove Point";
	glColor3f(1,0.5,0.2);
    renderString(str7.data(), str7.size(), 10, 265, 0);
    string str4 = "Press A: Add a Next Point  (need mouse pointer on Point)";
	glColor3f(1,1,1.0);
    renderString(str4.data(), str4.size(), 10, 250, 1);
	string str5 = "Press D: Delete Point  (need mouse pointer on Point)";
	glColor3f(1,1,1.0);
    renderString(str5.data(), str5.size(), 10, 230, 1);

	string str8 = "Resolution (Increase or Decrease)";
	glColor3f(1,0.5,0.2);
    renderString(str8.data(), str8.size(), 10, 200, 0);
	string str9 = "Press T: Increase Resolution";
	glColor3f(1,1,1.0);
    renderString(str9.data(), str9.size(), 10, 185, 1);
	string resolString = "resolution: ";
	glColor3f(1,1,1.0);
  	renderString(resolString.data(), resolString.size(), 250, 170, 2);
	glColor3f(1,1,0);
  	renderString(resolStr.data(), resolStr.size(), 340, 168, 0);
	string strA = "Press R: Decrease Resolution";
	glColor3f(1,1,1.0);
    renderString(strA.data(), strA.size(), 10, 165, 1);

	string strB = "Degree Order (Increase or Decrease)";
	glColor3f(1,0.5,0.2);
    renderString(strB.data(), strB.size(), 10, 135, 0);
	string strC = "Press P: Increase Order (need to Select B-Spline curve point)";
	glColor3f(1,1,1.0);
    renderString(strC.data(), strC.size(), 10, 120, 1);
	string order = "order: ";
	glColor3f(1,1,1.0);
    renderString(order.data(), order.size(), 290, 110, 2);
	glColor3f(0.1,0.8,0.4);
	if(chooseBS == true && !BSplineCurves[moveCurve].BSplinePoints.empty()){
		string curOrder = to_string(BSplineCurves.at(moveCurve).k);
		renderString(curOrder.data(), curOrder.size(), 342, 109, 0);
	}
	string strD = "Press O: Decrease Order";
	glColor3f(1,1,1.0);
    renderString(strD.data(), strD.size(), 10, 100, 1);
	string strK = "Press K: to modify knots value in next screen";
	glColor3f(1,1,1.0);
    renderString(strK.data(), strK.size(), 10, 70, 2);
	string strS = "Save";
	glColor3f(1,0.5,0.2);
    renderString(strS.data(), strS.size(), 10, 40, 0);
	string strEx = "Exit";
	glColor3f(1,0.5,0.2);
    renderString(strEx.data(), strEx.size(), 200, 40, 0);
	string strE = "Press W: Write Data to file";
	glColor3f(1,1,1.0);
    renderString(strE.data(), strE.size(), 10, 25, 1);
	string strF = "Press q: Exit the program";
	glColor3f(1,1,1.0);
    renderString(strF.data(), strF.size(), 200, 25, 1);
}
void knotsWinFunc(){
	if(chooseBS == true && !BSplineCurves[moveCurve].BSplinePoints.empty()){
		glColor3f(0.4,1.0,0.9);
		glRasterPos2f(0.17, 39);
      	renderKnotString(Time, "Knots", 0, 's');
		glColor3f(0.9,0.9,0.9);
		glRasterPos2f(0.5, 35);
		renderKnotString(Helve, "Click knots(t) value to", 0, 's');
		glRasterPos2f(0.45, 33.5);
		renderKnotString(Helve, "to insert new value and enter", 0, 's');
		glRasterPos2f(0.45, 30.5);
		renderKnotString(by9, "Press K: Main Menu Screen", 0, 's');
		glRasterPos2f(0.6, 27.5);
		renderKnotString(Helve, "Order(k): ", 0, 's');
		glColor3f(0.2,1,0.2);
		glRasterPos2f(0.79, 27.4);
		renderKnotString(Time, to_string(BSplineCurves[moveCurve].k), 0, 's');

		int knotSize = BSplineCurves.at(moveCurve).BStotalPoints.size() + degreeOrder;
		for(int i = 0; i < BSplineCurves[moveCurve].knotsVec.size(); i++){
			string T = "T";
			glColor3f(1,1,1);
			glRasterPos2f(0.1, 38 - i);
			renderKnotString(by9, T, 0, 's');
			string kt = to_string(i);
			glRasterPos2f(0.12, 37.8 - i);
			renderKnotString(GLUT_BITMAP_8_BY_13, kt, 0, 's');
			string ar = "->";
			glRasterPos2f(0.2, 38 - i);
			renderKnotString(Helve, ar, 0, 's');

			glColor3f(1,1.0,0.0);
			if(isKnotIn && isKnotPosition == i) continue;
			glRasterPos2f(0.3, 38 - i);
            renderKnotString(by9,"",BSplineCurves.at(moveCurve).getKnots(i), 'f');
		}
        if(isKnotIn){
			glRasterPos2d(0.3, 38 - isKnotPosition);
			renderKnotString(by9, knotStr, 0,'s');
			renderKnotString(by9, "_", 0, 's');
		}
	}
	else {
		string str = "Bezier curve is now selecting";
		glColor3f(0.4,1.0,0.9);
		renderString(str.data(), str.size(), 80, 250, 0);

		string str3 = "OR";
		glColor3f(1,1,1);
		renderString(str3.data(), str3.size(), 185, 230, 2);

		string str4 = "No curve. Press O or P to manipulate curve";
		glColor3f(0.4,1,0.9);
		renderString(str4.data(), str4.size(), 20, 210, 0);

		string str1 = "Please click the B-Spline Points";
		glColor3f(0.4,1.0,0.9);
		renderString(str1.data(), str1.size(), 65, 180, 0);
		string str2 = "to modify Knots";
		glColor3f(0.4,1.0,0.9);
		renderString(str2.data(), str2.size(), 125, 160, 0);
		glColor3f(1,1,1);
		string main = "Press K: Main Menu Screen";
		renderString(main.data(), main.size(), 200, 50, 3);
	}
}
void reshape(int width, int height) {
    screen_width = width;
    screen_height = height;
    glViewport(0, 0, width, height);
    gluOrtho2D(0, 800, 0, 800);
}
void GUIMouseFunc(int button, int state, int x, int y) {
	 if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (chooseBS) {
            isKnotPosition = y / 18 - 1;
			int knotSize = BSplineCurves.at(moveCurve).BStotalPoints.size() + degreeOrder;
            if (0 <= isKnotPosition && isKnotPosition < knotSize) {
                isKnotIn = true;
                knotStr.clear();
            }
        }
    }
    reDisplay();
}
float getFloat(const string& str){
	float stringToFloat;
	sscanf(str.c_str(), "%f", &stringToFloat);
    return stringToFloat;
}
// =======================================================================//
void drawPointLine(initialPoint start, initialPoint end, int color, char c, int id){
	float startx=(start.x/(screen_width/2))-1, starty=(start.y/(screen_height/2))-1;
	float endx=(end.x/(screen_width/2))-1, endy=(end.y/(screen_height/2))-1;
	switch (color){
	case 0: r = 8.0, g = 8.0, b = 0; break; // curve color
	case 1: r = 0.3, g = 0.6, b = 1; break; // BZ color
	case 2: r = 0.5, g = 0.8, b = 0.3; break; // BS color
	case 3: 
		if(moveCurve == id){
			r = 1.0, g = 0.2, b = 0.2;
		}
		else if(moveCurve != id && chooseBZ == true){
			r = 0.3, g = 0.6, b = 1;
		}
		else if(moveCurve != id && chooseBS == true){
			r = 0.5, g = 0.8, b = 0.3;
		} 
	 	break;
	default: break;
	}
	switch (c) {
	case 'p':
			glPointSize(12);
			glBegin(GL_POINTS);
			glColor3f(r,g,b);
			glVertex2f(startx,starty);
			glEnd(); break;
	case 'l':
			glLineWidth(2.4);
			glBegin(GL_LINES);
			glColor3f(r,g,b);
			glVertex2f(startx,starty);
			glVertex2f(endx,endy);
			glEnd(); break;
	default: break;
	}
}
void mouse(int button, int state, int x, int y) {
	bool isBezier = false;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		int winX, winY;
		Bezier BZcurveObj; BSpline BScurveObj;
		winX = x; winY = screen_height - y;
		if (addBZcurve == true || addBScurve == true) {
			if (addBZcurve == true) { // new BZ curve
				PointObj.x = winX; PointObj.y = winY;
				BZcurveObj.BZtotalPoints.push_back(PointObj);
				BezierCurves.push_back(BZcurveObj);
				BZcurveObj.BZtotalPoints.clear();
				addBScurve = false; addBZcurve = false;
			}
			else if (addBScurve == true && chooseBS == true) { // new BS curve
				PointObj.x = winX; PointObj.y = winY;
				BScurveObj.BStotalPoints.push_back(PointObj);
				BScurveObj.k = 2;
				BSplineCurves.push_back(BScurveObj);
				BScurveObj.BStotalPoints.clear();
				addBScurve = false; addBZcurve = false;
			}
		}
		else {
			for (int i = 0; i < BSplineCurves.size(); i++) {
				if (!BSplineCurves.at(i).BStotalPoints.empty()) { int j = 0;
					while(j < BSplineCurves.at(i).BStotalPoints.size()) {
						float xBS = winX - BSplineCurves.at(i).BStotalPoints.at(j).x, yBS = winY - BSplineCurves.at(i).BStotalPoints.at(j).y;
						if (xBS >= -12 &&  xBS <= 12 && yBS >= -12 && yBS <= 12) {
							isBezier = false;	mouseMove = true;
							isPointMove = true; curveType = 2; 
							moveCurve = i; 		movePoint = j;
							chooseBZ = false; 	chooseBS = true;
						}
						else {
							if (mouseMove == false) {
								isBezier = true;
								isPointMove = false;
							}
							if (addBSplinePoint == true){ // add next BS point
								PointObj.x = winX;
								PointObj.y = winY;
								BSplineCurves.at(moveCurve).BStotalPoints.insert(BSplineCurves.at(moveCurve).BStotalPoints.begin()+movePoint+1, PointObj);
								addBSplinePoint = false;
							}
						}
						j = j + 1;
					}
				}
			}
			if (true) { int i = 0;
				while(i < BezierCurves.size()) {
					if (!BezierCurves.at(i).BZtotalPoints.empty()) {
						for (int j = 0; j < BezierCurves.at(i).BZtotalPoints.size(); j++) {
							float xBZ = winX - BezierCurves.at(i).BZtotalPoints.at(j).x, yBZ = winY - BezierCurves.at(i).BZtotalPoints.at(j).y;
							if (xBZ >= -12 &&  xBZ <= 12 && yBZ >= -12 && yBZ <= 12) {
								isPointMove = true;
								mouseMove = true;
								curveType = 1;
								moveCurve = i;
								movePoint = j;
								chooseBZ = true;
								chooseBS = false;
							}
							else {
								if (mouseMove == false) {
									isBezier = true;
									isPointMove = false;
								}
								if (addBezierPoint == true) { // add new BZ point
									PointObj.x = winX;
									PointObj.y = winY;
									BezierCurves.at(moveCurve).BZtotalPoints.insert(BezierCurves.at(moveCurve).BZtotalPoints.begin()+movePoint+1, PointObj);
									addBezierPoint = false;
								}
							}
						}
					}
					i = i + 1;
				}
			}
		}
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (isPointMove == true) {
			if (curveType == 2) {
				BSplineCurves.at(moveCurve).BStotalPoints.at(movePoint).x = x;
				BSplineCurves.at(moveCurve).BStotalPoints.at(movePoint).y = screen_height-y;
				mouseMove = false;
			}
			if (curveType == 1) {
				BezierCurves.at(moveCurve).BZtotalPoints.at(movePoint).x = x;
				BezierCurves.at(moveCurve).BZtotalPoints.at(movePoint).y = screen_height-y;
				mouseMove = false;
			}
			isPointMove = false;
		}
	}
	reDisplay();
}
//gets called when the curser moves accross the scene
void motion(int x, int y){
	int winX = x;
	int winY = screen_height- y;
	if (mouseMove == true) {
		if (curveType == 1) {
			BezierCurves.at(moveCurve).BZtotalPoints.at(movePoint).x = winX;
			BezierCurves.at(moveCurve).BZtotalPoints.at(movePoint).y = winY;
		}
		if (curveType == 2) {
			BSplineCurves.at(moveCurve).BStotalPoints.at(movePoint).x = winX;
			BSplineCurves.at(moveCurve).BStotalPoints.at(movePoint).y = winY;
		}
	}
	reDisplay();
}
void keyBoardFunc(unsigned char keys, int x, int y){
	int winX = x, winY = screen_height - y;
	bool onPoint = false;
	bool isBezier = true;
	for (int i = 0; i < BSplineCurves.size(); i++) {
		if (!BSplineCurves.at(i).BStotalPoints.empty()) {
			for (int j = 0; j < BSplineCurves.at(i).BStotalPoints.size(); j++) {
				float xBS = winX - BSplineCurves.at(i).BStotalPoints.at(j).x, yBS = winY - BSplineCurves.at(i).BStotalPoints.at(j).y;
				if (xBS >= -12 && xBS <= 12 && yBS  >= -12 && yBS <= 12) {
					onPoint = true;
					curveType = 2;
					moveCurve = i;
					movePoint = j;
					break;
				}
				else {
					onPoint = false;
					isBezier = true;
				}
			}
			if (onPoint == true) {
				isBezier = false;
				break;
			}
		}
	}
	if (isBezier == true) {
		for (int i = 0; i < BezierCurves.size(); i++) {
			if (!BezierCurves.at(i).BZtotalPoints.empty()) {
				for (int j = 0; j < BezierCurves.at(i).BZtotalPoints.size(); j++) {
					float xBZ = winX - BezierCurves.at(i).BZtotalPoints.at(j).x, yBZ = winY - BezierCurves.at(i).BZtotalPoints.at(j).y;
					if (xBZ >= -12 && xBZ <= 12 && yBZ  >= -12 && yBZ <= 12) {
						onPoint = true;
						curveType = 1;
						moveCurve = i;
						movePoint = j;
						isBezier = false;
						break;
					}
					else{
						onPoint = false;
					}
				}
				if (onPoint == true) {
					break;
				}
			}
		}
	}
	switch (keys) {
		case 'z': case 'Z' :// new BZ
			chooseBZ = true; chooseBS = false;
			addBZcurve = true; addBScurve = false; break;
		case 's': case 'S': // new BS
			chooseBS = true; chooseBZ = false;
			addBZcurve = false; addBScurve = true;	break;
		case 'a': case 'A':// add point
			if (curveType == 1 && onPoint == true) {
				chooseBZ = true; chooseBS = false;
				addBezierPoint = true; addBSplinePoint = false;
			}
			if (curveType == 2 && onPoint == true) {
				BSplineCurves.at(moveCurve).knotVerify = false;
				chooseBS = true; chooseBZ = false;
				addBSplinePoint = true; addBezierPoint = false;
			}	break;
		case 'd': case 'D': // delete point
			if (curveType == 1 && onPoint == true) {
				BezierCurves.at(moveCurve).BZtotalPoints.erase(BezierCurves.at(moveCurve).BZtotalPoints.begin()+movePoint);
				if (BezierCurves.at(moveCurve).BZtotalPoints.empty()) {
						BezierCurves.erase(BezierCurves.begin()+moveCurve);
				}
			}
			if (curveType == 2 && onPoint == true) {
				BSplineCurves.at(moveCurve).knotVerify = false;
				BSplineCurves.at(moveCurve).BStotalPoints.erase(BSplineCurves.at(moveCurve).BStotalPoints.begin()+movePoint);
				if (BSplineCurves.at(moveCurve).BStotalPoints.empty()) {
					BSplineCurves.erase(BSplineCurves.begin()+moveCurve);
				}
			}	break;
		case 't':case 'T': // resolution
			resolution = resolution + 1;
			resolStr = to_string(resolution); break;
		case 'r':case 'R':
			resolution = resolution - 1;
			if(resolution < 1){
				resolution = 1;
			} 
			resolStr = to_string(resolution); break;
		case 'p': case 'P':// BS order increase
			if(chooseBS == true){
				BSplineCurves.at(moveCurve).knotVerify = false;
				degreeOrder = degreeOrder + 1;
				if (degreeOrder > BSplineCurves.at(moveCurve).BStotalPoints.size()){
					degreeOrder = BSplineCurves.at(moveCurve).BStotalPoints.size();
				}
				else if(degreeOrder < 2){
					degreeOrder = 2;
				}
				BSplineCurves.at(moveCurve).k = degreeOrder;
				orderString = to_string(degreeOrder);
			}
			else{break;} break;
		case 'o': case 'O': // BS order decrease
			if(chooseBS == true){
				BSplineCurves.at(moveCurve).knotVerify = false;
				degreeOrder = degreeOrder - 1;
				if (degreeOrder > BSplineCurves.at(moveCurve).BStotalPoints.size()){
					degreeOrder = BSplineCurves.at(moveCurve).BStotalPoints.size();
				}
				else if(degreeOrder < 2){
					degreeOrder = 2;
				}
				BSplineCurves.at(moveCurve).k = degreeOrder;
				orderString = to_string(degreeOrder);
			} 
			else{
				break;
			}break;
		// knots modify
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8':
		case '9': case '0': case '.':
		if (isKnotIn) knotStr += keys; break;
        case '\r':
            if (isKnotIn) isKnotIn = false;
            if (chooseBS)
				BSplineCurves.at(moveCurve).position = isKnotPosition;
				BSplineCurves.at(moveCurve).newKnot = getFloat(knotStr);
				BSplineCurves.at(moveCurve).knotVerify = true;
            break;
        case '\177': // delete input string
            if (isKnotIn && knotStr.size()) knotStr.erase(knotStr.size() - 1);
            break;
        case '\033': // esc from string
            if (isKnotIn) isKnotIn = false; break;
		case 'w': case 'W': //break; // save data
			if (!BSplineCurves.empty() || !BezierCurves.empty()) {
				cout << "Write Data in file" << endl << endl;
				saveFile();
			}	break;
		case 'k': case 'K': toggle = !toggle; break;
		case 'q': case 'Q': 
			saveFile(); cout << "Any change will be saved in the original file the data is read in. \n" <<  "Bye Bye!!" << endl; exit(0);break;
		default: break;
	}
	reDisplay();
}



