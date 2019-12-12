#include "main.h"
void DrawBSplineCurves(){
	for (int i = 0; i < BSplineCurves.size(); i++) { // Draw BS Point && line 
		if (!BSplineCurves.at(i).BStotalPoints.empty()) {
			BSplineCurves.at(i).deBoorAlgo(resolution);
			if(chooseBS == true){
				chooseCurve = "B-Spline";
				for (int j = 0; j < BSplineCurves.at(i).BStotalPoints.size()-1; j++) { // Line
					drawPointLine(BSplineCurves.at(i).BStotalPoints.at(j), BSplineCurves.at(i).BStotalPoints[j+1], 3, 'l', i);
				}
				for (int j = 0; j < BSplineCurves.at(i).BStotalPoints.size(); j++) { // Point
					drawPointLine(BSplineCurves.at(i).BStotalPoints.at(j), BSplineCurves.at(i).BStotalPoints[j+1], 3, 'p', i);
				}
			}
			else{
				for (int j = 0; j < BSplineCurves.at(i).BStotalPoints.size()-1; j++) { // Line
					drawPointLine(BSplineCurves.at(i).BStotalPoints.at(j), BSplineCurves.at(i).BStotalPoints[j+1], 2, 'l', i);
				}
				for (int j = 0; j < BSplineCurves.at(i).BStotalPoints.size(); j++) { // Point
					drawPointLine(BSplineCurves.at(i).BStotalPoints.at(j), BSplineCurves.at(i).BStotalPoints[j+1], 2, 'p', i);
				}
			}
		}
		if (!BSplineCurves.at(i).BSplinePoints.empty()) { // draw BS curve
			for (int j = 0; j < BSplineCurves.at(i).BSplinePoints.size()-1; j++) {
				drawPointLine(BSplineCurves.at(i).BSplinePoints.at(j), BSplineCurves.at(i).BSplinePoints[j+1],0, 'l', i);
			}
		}
	}
}
float BSpline::getKnots(int position) const {
    if (0 <= position && position < knotsVec.size())
        return knotsVec[position];
}
void BSpline::deBoorAlgo(int resolution){
    this->k = k;
	if(!BSplinePoints.empty() || !knotsVec.empty()){
		if (!BSplinePoints.empty()) {
			BSplinePoints.clear();
		}
		if(knotVerify == false){
			if(!knotsVec.empty()){
			knotsVec.clear();
			}
		}
	}
   if (k != 1) {
      float order = (float)k -1, increment;
		increment = 1/(float)resolution;
		if(knotVerify == false){
			for (int i = 0; i < BStotalPoints.size() + k; i++) {
			knotsVec.push_back(i);
			}
		}
		if(knotVerify){
			knotsVec.erase(knotsVec.begin() +position);
			knotsVec.insert(knotsVec.begin() + position, newKnot);
		}
		for (float i = order; i < knotsVec[BStotalPoints.size()]; i  = i + increment) {
			initialPoint newBSpoint[A][A]; int n = 0, It = 0;
			while(n < BStotalPoints.size()) {
				newBSpoint[n][0].x = BStotalPoints[n].x;
				newBSpoint[n][0].y = BStotalPoints[n].y;
				n = n + 1;
			}
			for(int j = 0; j < knotsVec.size(); j++) {
				if( order < knotsVec[j+1]&& order >= knotsVec[j] ) {
					It = knotsVec[j];
					break;
				}
			}
			for(int j = 1; j <= k-1; j++) {
				for(int i = (It - (k - 1)); i <= (It - j); i++) {
					float b1 = knotsVec[i+k] - order;
					float b2 = order - knotsVec[i+j];
					newBSpoint[i][j].x = (b1/(knotsVec[i+k] - knotsVec[i+j]))*newBSpoint[i][j-1].x + 
												(b2/(knotsVec[i+k] - knotsVec[i+j]))*newBSpoint[i+1][j-1].x;
					newBSpoint[i][j].y = (b1/(knotsVec[i+k] - knotsVec[i+j]))*newBSpoint[i][j-1].y + 
												(b2/(knotsVec[i+k] - knotsVec[i+j]))*newBSpoint[i+1][j-1].y;
				}
			}
			BSplinePoints.push_back(newBSpoint[It-k+1][k-1]);
			order = order + increment;
		}
	}
}
