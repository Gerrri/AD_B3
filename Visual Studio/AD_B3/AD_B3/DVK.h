#pragma once
using namespace std;
#include <iostream>
#include "GEOKO.h"

class DVK
{
public:
	//Konstruktor
	DVK(long Anzahl) ;

	//Nur Heapsort!
	//void heapDown(long Anzahl, long Knoten);
	//void erzeugeHeap(long Anzahl);
	void vertausche(long First, long Second);
	




private:
	//Konstruktor

	//void HeapSort() ;// in DVK Konstruktor
	string Menu() ; // Menü zur abfrage der der Datei
	void readData(string choice);

	//Varaibalen zu Verankerung / Mitte
	GEOKO *V_Anker;
	GEOKO *N_Anker;
	GEOKO *middle;

	

	int anz = 0;

	
	

	

};

