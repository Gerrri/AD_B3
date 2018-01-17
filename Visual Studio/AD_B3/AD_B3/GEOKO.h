#pragma once
#include "DVKE.h"
class GEOKO :
	public DVKE
{
public:
	//Konstruktor -> Aless auf NULL
	GEOKO();
	
	//Getter
	int GetBrGr() const { return BrGr; }
	int GetLaGr() const { return LaGr; }
	int GetBrMin() const { return BrMin; }
	int GetLaMin() const { return LaMin; }
	double GetBrSec() const { return BrSec; }
	double GetLaSec() const { return LaSec; }


	//Setter
	void SetBrGr(int BrGr) { this->BrGr = BrGr; }
	void SetLaGr(int LaGr) { this->LaGr = LaGr; }
	void SetBrMin(int BrMin) { this->BrMin = BrMin; }
	void SetLaMin(int LaMin) { this->LaMin = LaMin; }
	void SetBrSec(double BrSec) { this->BrSec = BrSec; }
	void SetLaSec(double LaSec) { this->LaSec = LaSec; }

	//Ausgabe als Zeile auf Konsole
	void console_output();



private:
	int BrGr;
	int LaGr;
	int BrMin;
	int LaMin;
	double BrSec;
	double LaSec;

};

