#pragma once
#include "DVKE.h"
#include "GEOKO.h"
#include <string>
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
	int Geta_num() const { return a_num; }



	//Setter
	void SetBrGr(int BrGr) { this->BrGr = BrGr; }
	void SetLaGr(int LaGr) { this->LaGr = LaGr; }
	void SetBrMin(int BrMin) { this->BrMin = BrMin; }
	void SetLaMin(int LaMin) { this->LaMin = LaMin; }
	void SetBrSec(double BrSec) { this->BrSec = BrSec; }
	void SetLaSec(double LaSec) { this->LaSec = LaSec; }
	void Seta_num(int a_num) { this->a_num = a_num; }


	//�berladungen
	double operator-(GEOKO& in);

	//Ausgabe als Zeile auf Konsole
	void console_output();

	// R�ckgabe eines Strings mit den werten des Objekts
	string filestring();



private:
	int BrGr;
	int LaGr;
	int BrMin;
	int LaMin;
	double BrSec;
	double LaSec;

	//f�r heapsort , wegen der geforderten funktion mit long werten bei tauschen
	int a_num;
};

