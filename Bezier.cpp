#include "main.h"

void DrawBezierCurves(){
	for (int i = 0; i < BezierCurves.size(); i++) {
		if (!BezierCurves.at(i).BZtotalPoints.empty()) { // Draw Bezier Line && Point
			BezierCurves.at(i).deCastelAlgo(resolution);
			if(chooseBZ == true){
				chooseCurve = "Bezier";
				for (int j = 0; j < BezierCurves.at(i).BZtotalPoints.size()-1; j++) { // Line
					drawPointLine(BezierCurves.at(i).BZtotalPoints.at(j), BezierCurves.at(i).BZtotalPoints[j+1], 3, 'l', i);
				}
				for (int j = 0; j < BezierCurves.at(i).BZtotalPoints.size(); j++) { // Point
					drawPointLine(BezierCurves.at(i).BZtotalPoints.at(j), BezierCurves.at(i).BZtotalPoints[j+1], 3, 'p', i);
				}
			}
			else{
				for (int j = 0; j < BezierCurves.at(i).BZtotalPoints.size()-1; j++) { // Line
					drawPointLine(BezierCurves.at(i).BZtotalPoints.at(j), BezierCurves.at(i).BZtotalPoints[j+1], 1, 'l', i);
				}
				for (int j = 0; j < BezierCurves.at(i).BZtotalPoints.size(); j++) { // Point
					drawPointLine(BezierCurves.at(i).BZtotalPoints.at(j), BezierCurves.at(i).BZtotalPoints[j+1], 1, 'p', i);
				}
			}
		}
		if (!BezierCurves.at(i).BezierPoints.empty()) { // Draw BZ curve
			for (int j = 0; j < BezierCurves.at(i).BezierPoints.size()-1; j++) {
				drawPointLine(BezierCurves.at(i).BezierPoints.at(j), BezierCurves.at(i).BezierPoints[j+1],0, 'l', i);
			}
		}
	}
}
void Bezier::deCastelAlgo(int resolution) {
        std::vector<initialPoint> BezierNewTotalPoint;
        initialPoint newBZpoint;
        float t = 0, increment, resol = 0, k = 0;
        increment = 1/(float)resolution;
        if(!BezierNewTotalPoint.empty() || !BezierPoints.empty() ){
            if (!BezierPoints.empty()) {
                BezierPoints.clear();
            }
            if (!BezierNewTotalPoint.empty()) {
                BezierNewTotalPoint.clear();
            }
        }
        while(resol <= resolution) {
            BezierNewTotalPoint = BZtotalPoints;
            for (int i = 1; i < BZtotalPoints.size(); i++) {
                for (int j = 0; j < (BZtotalPoints.size() - i); j++) {
                    newBZpoint.x = (1-t)*BezierNewTotalPoint[j].x + t*BezierNewTotalPoint[j+1].x;
                    newBZpoint.y = (1-t)*BezierNewTotalPoint[j].y + t*BezierNewTotalPoint[j+1].y;
                    BezierNewTotalPoint[j] = newBZpoint;
                }
            }
            BezierPoints.push_back(BezierNewTotalPoint[k]);
            t = t + increment; resol = resol + 1;
        }
    }