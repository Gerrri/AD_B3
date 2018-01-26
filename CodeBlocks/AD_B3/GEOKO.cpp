#include "stdafx.h"
#include "GEOKO.h"
#include <iostream>
#include <string>
#include "math.h"
using namespace std;

GEOKO::GEOKO() : BrGr(NULL), LaGr(NULL), BrMin(NULL), LaMin(NULL), BrSec(NULL), LaSec(NULL), DVKE()
{
}

void GEOKO::console_output() {
	cout<< "(" << to_string(aus_csvB) << "/" << to_string(aus_csvL) << ")" << " || "<< "("<< BrGr << "/" << LaGr <<")  "<<"||"<<"  (" << BrMin << "/" << LaMin << ")  " <<"||"<< "  (" << BrSec << "/" << LaSec << ")" <</*" ###[Format: (LängenGrad/BreitenGrad) || (LängenMinute/BreitenMinute) || (LängenSekunde/BreitenSekunde])" <<*/endl;
}


// rückgabe von Differenz GEOKO zur mitte
double GEOKO::operator-(GEOKO &in) {
	double sec1_B, sec1_L;
	double sec2_B, sec2_L;
	double distance;

	sec1_B = this->aus_csvB;
	sec1_L = this->aus_csvL;

	sec2_B = in.aus_csvB;
	sec2_L = in.aus_csvL;


	distance = sqrt(pow(sec1_B - sec2_B, 2) + pow(sec1_L - sec2_L, 2));

	return distance;
}

double GEOKO::abstand(GEOKO in) {
	double sec1_B, sec1_L;
	double sec2_B, sec2_L;
	double distance;

	sec1_B = this->aus_csvB;
	sec1_L = this->aus_csvL;

	sec2_B = in.aus_csvB;
	sec2_L = in.aus_csvL;


	distance = sqrt(pow(sec1_B - sec2_B, 2) + pow(sec1_L - sec2_L, 2));
	//distance = sqrt((sec1_B - sec2_B, 2)*(sec1_B - sec2_B, 2) + (sec1_L - sec2_L, 2)*(sec1_L - sec2_L, 2));

	return distance;
}
//string & GEOKO::filestring(string & n){
	//char*  a = "(" + to_string(this->BrGr) + "/" + to_string(this->LaGr) + ")  " + "||" + "  (" + to_string(this->BrMin) + "/" + to_string(this->LaMin) + ")  " + "||" + "  (" + to_string(this->BrSec) + "/" + to_string(this->LaSec) + ")";
	//n.clear(); // string leeren
	//n = "(" + to_string(BrGr) + "/" + to_string(LaGr) + ")  " + "||" + "  (" + to_string(BrMin) + "/" + to_string(LaMin) + ")  " + "||" + "  (" + to_string(BrSec) + "/" + to_string(LaSec) + ")";

	//return n;
//}