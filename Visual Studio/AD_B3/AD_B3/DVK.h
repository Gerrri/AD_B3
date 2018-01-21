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
	//void heapDown(long Anzahl, long Knoten);
	//void erzeugeHeap(long Anzahl);
	void vertausche(long First, long Second);
	void HeapSort();// in DVK Konstruktor
	void MaxHeap(); // erzeug maxheap
	void console_output_list(); // vosichtig ! gibt alle elemente aus !
	void create_File(string choice);

private:
	//Konstruktor

	
	string Menu() ; // Menü zur abfrage der der Datei
	void readData(string choice);
	
	//Varaibalen zu Verankerung / Mitte
	GEOKO *V_Anker;
	GEOKO *N_Anker;
	GEOKO *middle;

	int anz = 0;	 // anzahl objekte im array
	int anz_uns = 0; // anzahl der unsortieren elemente im array (von links)

	
	

	

};

