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

	//MergeSort	
	void MergeSort();
	void sortieren(GEOKO * Liste[], int länge);
	GEOKO ** copy2(GEOKO * Liste[], int anz);
	
	//Heapsort!
	void heapDown(int anz_uns);
	void initMaxheap();
	void vertausche(long First, long Second);
	void HeapSort(); // in DVK Konstruktor
	void console_output_list(); // vosichtig ! gibt alle elemente aus !
	void create_File();

	//not in use
	void copy(GEOKO * E1, GEOKO * E2);

private:
	//Konstruktor

	
	string Menu() ; // Menü zur abfrage der der Datei
	void readData(string choice);
	
	//Varaibalen zu Verankerung / Mitte
	GEOKO *V_Anker;
	GEOKO *N_Anker;
	GEOKO *middle;

	int anz ;	 // anzahl objekte im array
	

	
	

	

};

