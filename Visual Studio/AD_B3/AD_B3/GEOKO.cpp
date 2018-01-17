#include "stdafx.h"
#include "GEOKO.h"
#include <iostream>
using namespace std;

GEOKO::GEOKO() : BrGr(NULL), LaGr(NULL), BrMin(NULL), LaMin(NULL), BrSec(NULL), LaSec(NULL), DVKE()
{
}

void GEOKO::console_output() {
	cout<<"("<< BrGr << "/" << LaGr <<")  "<<"||"<<"  (" << BrMin << "/" << LaMin << ")  " <<"||"<< "  (" << BrSec << "/" << LaSec << ")" <<" ###[Format: (L�ngenGrad/BreitenGrad) || (L�ngenMinute/BreitenMinute) || (L�ngenSekunde/BreitenSekunde])" <<endl;
}