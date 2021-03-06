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
	double Getaus_csvB() const { return aus_csvB; }
	double Getaus_csvL() const { return aus_csvL; }
	double Getdist() const { return dist; }


	//Setter
	void SetBrGr(int BrGr) { this->BrGr = BrGr; }
	void SetLaGr(int LaGr) { this->LaGr = LaGr; }
	void SetBrMin(int BrMin) { this->BrMin = BrMin; }
	void SetLaMin(int LaMin) { this->LaMin = LaMin; }
	void SetBrSec(double BrSec) { this->BrSec = BrSec; }
	void SetLaSec(double LaSec) { this->LaSec = LaSec; }
	void Seta_num(int a_num) { this->a_num = a_num; }
	void Setaus_csvB(double aus_csvB) { this->aus_csvB = aus_csvB; }
	void Setaus_csvL(double aus_csvL) { this->aus_csvL = aus_csvL; }
	void Setdist(double dist) { this->dist = dist; }


	//�berladungen
	double operator-(GEOKO& in);
	double abstand(GEOKO in);

	//Ausgabe als Zeile auf Konsole
	void console_output();

	// R�ckgabe eines Strings mit den werten des Objekts
	//string& filestring(string & n);




private:

	//zum Debuggen
	double aus_csvB;
	double aus_csvL;

	int BrGr;
	int LaGr;
	int BrMin;
	int LaMin;
	double BrSec;
	double LaSec;

	double dist;// abstand zum Mittelpunkt

	

	//f�r heapsort , wegen der geforderten funktion mit long werten bei tauschen
	int a_num;
};

