#include "main.h"

void readFile() {
    char curveType, order;
    BSpline BScurves;
    Bezier BZcurves;
    vector<initialPoint> BSpoint, BZpoint;
  	vector<double> data;
		myFile.open(fileName);
		if (!myFile) {
			cerr << "Unable to open file!\n";
			exit(0);
		}
		while(myFile >> totalObjects){
			data.push_back(totalObjects);
		}
		myFile.close();
		auto num = data.begin();
		int totalLine = (int)*num;
		for(int i = 0; i < totalLine; i++){
			curveType = *(++num);
			if(curveType == 1){
				totalPoints = *(++num);
				for(int j = 0; j < totalPoints; j++){
					PointObj.x = *(++num);
					PointObj.y = *(++num);
					BZpoint.push_back(PointObj);
				}
				BZcurves.index = i;
				BZcurves.BZtotalPoints = BZpoint;
				BezierCurves.push_back(BZcurves);
				
				BZcurves.BZtotalPoints.clear();
				BZpoint.clear();
			}
			else if(curveType == 2){
				totalPoints = *(++num);
				order = *(++num);
				for(int i = 0; i < totalPoints; i++){
					PointObj.x = *(++num);
					PointObj.y = *(++num);
					BSpoint.push_back(PointObj);
				}
				BScurves.index = i;
				BScurves.BStotalPoints = BSpoint;
				BScurves.k = order;
				BSplineCurves.push_back(BScurves);
				BScurves.BStotalPoints.clear();
				BSpoint.clear();
			}
		}
}
void saveFile() {
	char curveType;
	int order;
	BSpline BScurves;
	Bezier BZcurves;
	vector<initialPoint> BSpoint, BZpoint;
	myFile.open (fileName, ios::out | ios::trunc);
	if (myFile.is_open()) {
		myFile << BSplineCurves.size() + BezierCurves.size() << endl;
		int i = 0;
		while(i < BezierCurves.size()) {
			myFile << endl;
			myFile << 1 << endl;
			myFile << BezierCurves[i].BZtotalPoints.size() << endl;
			
			for (int j = 0; j < BezierCurves.at(i).BZtotalPoints.size() ; j++) {
				myFile << BezierCurves.at(i).BZtotalPoints.at(j).x;
				myFile << ' ' ;
				myFile << BezierCurves.at(i).BZtotalPoints.at(j).y;
				myFile << endl ;
			}
			i = i + 1;
		}
		int k = 0;
		while(k < BSplineCurves.size()) {
			myFile << endl;
			myFile << 2 << endl;
			myFile << BSplineCurves.at(k).BStotalPoints.size() << endl;
			myFile << BSplineCurves.at(k).k << endl;
			for (int j = 0; j < BSplineCurves.at(k).BStotalPoints.size() ; j++) {
				myFile << BSplineCurves.at(k).BStotalPoints.at(j).x;
				myFile << ' ' ;
				myFile << BSplineCurves.at(k).BStotalPoints.at(j).y;
				myFile << endl ;
			}
			k = k + 1;
		}
	}
	myFile.close();
}
void renderString(const char* text, int length, int x, int y, int id){
    glMatrixMode(GL_PROJECTION);
    double *array = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX,array);
    glLoadIdentity();
    glOrtho(0,400, 0, 400, -1,3);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);
    for(int i = 0; i < length; i++){
        switch (id){
        case 0:
            glutBitmapCharacter(Time, (int)text[i]); break;
        case 1:
            glutBitmapCharacter(Helve12, (int)text[i]); break;
		case 2: 
		    glutBitmapCharacter(Helve, (int)text[i]); break;
		case 3: 
			glutBitmapCharacter(by9, (int)text[i]);
        default:
            break;
        }
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(array);
    glMatrixMode(GL_MODELVIEW);
}
void renderKnotString(void* format, const string& str, float num, char i){
	char buf[10];
	switch (i){
	case 's':
		for (int i = 0; i < str.size(); i++)
			glutBitmapCharacter(format, str[i]); break;
	case 'f':
		sprintf(buf, "%.3f", num);
		renderKnotString(format, string(buf), 0, 's'); break;
	default: break;
	}
}