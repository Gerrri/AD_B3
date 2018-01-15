#pragma once
using namespace std;
#include <iostream>
#include "GEOKO.h"

class DVK
{
public:
	//Konstruktor
	DVK(long Anzahl) {};

	//Nur Heapsort!
	void heapDown(long Anzahl, long Knoten);
	void erzeugeHeap(long Anzahl);
	void vertausche(long First, long Second);
	void init();

private:
	//Konstruktor

	void HeapSort() {};// in DVK Konstruktor
	string Menu() {}; // Men� zur abfrage der der Datei
	void readData(string choice);

	//Varaibalen zu Verankerung / Mitte
	GEOKO *V_Anker;
	GEOKO *N_Anker;
	GEOKO *middle;

	// f�r initialisierung
	GEOKO *index[50];

	int anz = 0;

	
	

	readData(string choice);

};
