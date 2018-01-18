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
	cout<<"("<< BrGr << "/" << LaGr <<")  "<<"||"<<"  (" << BrMin << "/" << LaMin << ")  " <<"||"<< "  (" << BrSec << "/" << LaSec << ")" <<" ###[Format: (LängenGrad/BreitenGrad) || (LängenMinute/BreitenMinute) || (LängenSekunde/BreitenSekunde])" <<endl;
}


// rückgabe von Differenz GEOKO zur mitte
double GEOKO::operator-(GEOKO &in) {
	double sec1_B, sec1_L;
	double sec2_B, sec2_L;
	double distance;

	sec1_B = (this->BrGr * 3600) + (this->BrMin * 60) + this->BrSec;
	sec1_L = (this->LaGr * 3600) + (this->LaMin * 60) + this->LaSec;

	sec2_B = (in.GetBrGr() * 3600) + (in.GetBrMin() * 60) + in.GetBrSec();
	sec2_L = (in.GetLaGr() * 3600) + (in.GetLaMin() * 60) + in.GetLaSec();


	distance = sqrt(pow(sec1_B - sec1_L, 2) + pow(sec2_B - sec2_L, 2));

	return distance;
}

string GEOKO::filestring(){
	
	string  a = "(" + to_string(BrGr) + "/" + to_string(LaGr) + ")  " + "||" + "  (" + to_string(BrMin) + "/" + to_string(LaMin) + ")  " + "||" + "  (" + to_string(BrSec) + "/" + to_string(LaSec) + ")";
	
	return a;
}