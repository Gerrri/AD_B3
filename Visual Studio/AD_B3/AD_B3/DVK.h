#pragma once
using namespace std;
#include <iostream>
#include "GEOKO.h"
#include "GEONode.h"

class DVK
{
public:
	//Konstruktor
	DVK(long Anzahl) ;


	//Nur Heapsort!
	void heapDown(int anz_uns);
	//void erzeugeHeap(long Anzahl);
	void initMaxheap();
	void vertausche(long First, long Second);
	void copy(GEOKO * E1, GEOKO * E2);
	void HeapSort();// in DVK Konstruktor
	void console_output_list(); // vosichtig ! gibt alle elemente aus !
	void create_File();


private:
	//Konstruktor

	
	string Menu() ; // Menü zur abfrage der der Datei
	void readData(string choice);
	
	//Varaibalen zu Verankerung / Mitte
	GEOKO *V_Anker;
	GEOKO *N_Anker;
	GEOKO *middle;

	int anz = 0;	 // anzahl objekte im array
	

	
	

	

};

