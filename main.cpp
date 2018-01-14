#include <iostream>

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include "windows.h"
#include <iostream>
#include "math.h"

int main(){ 
DVK * pDVK = NULL;

//...Menue ...

// ...Auswahl ...



//----------------------------------------------------------------------
//
//    Zeitmessung im ms-Bereich
//    TESTANWENDUNG
//    Author: tbird
//    Date: 20.11.2007
//
//----------------------------------------------------------------------
	//Variablen
   
    LONGLONG g_Frequency, g_FirstNullCount, g_LastNullCount, g_FirstCount, g_LastCount;

    //Frequenz holen
    if (!QueryPerformanceFrequency((LARGE_INTEGER*)&g_Frequency))
        printf("Performance Counter nicht vorhanden");

	double resolution = 1000000 / ((double)g_Frequency);
	
	printf("Frequenz des Counters:  %lld kHz\n", g_Frequency/1000);  //lld -> LONGLONG darstellung
	printf("Dadurch maximale Aufloesung: %4.5f us\n", resolution);

	//null-messung
	QueryPerformanceCounter((LARGE_INTEGER*)&g_FirstNullCount);
	QueryPerformanceCounter((LARGE_INTEGER*)&g_LastNullCount);
	double nulltime = (((double)(g_LastNullCount-g_FirstNullCount))/((double)g_Frequency)); 

	printf("Null-Zeit: %4.5f us\n", nulltime * 1000000);
	
	//beginn messung
	QueryPerformanceCounter((LARGE_INTEGER*)&g_FirstCount);



// Hier ist der Aufruf fuer Ihr Sortierverfahren, Beispiel: Heap
//   pDVK->HeapSort();



	//2. Messung
    	QueryPerformanceCounter((LARGE_INTEGER*)&g_LastCount);

    	double dTimeDiff = (((double)(g_LastCount-g_FirstCount))/((double)g_Frequency)); 

//Von der gemessenen Zeit die "Null-Zeit" abziehen, um genauer zu werden
	double time = (dTimeDiff - nulltime) * 1000000; //mikro-sekunden
	printf("Zeit: %4.5f us\n" ,time);

        
//        Zurück ins Menü
}


